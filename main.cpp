#include "conversor.cpp"

int main (int argc, char** argv)
{
    //INICIALIZAÇÕES
    //video inicial
    int key = 1024;
    mode = 0;
    //0 CODIFICA
    //1 DECODIFICA
    //2 MELHORAMENTO DE IMAGEM RUIDOSA
    //3 IDENTIFICAÇÃO DE OBJETOS EM IMAGEM RUIDOSA
    char* in;
    char* out;

    in = argv[1];
    out = argv[2];

    //menu de opções
	printf(" Modos Disponíveis:\n (0)Criptografar\n (1)Descriptografar\n (2)Melhorar Imagem Ruidosa\n (3)Encontrar objeto em imagem Ruidosa\n\n  Digite o numero do modo escolhido: ");
	scanf("%d", &mode);
	if(mode>3||mode<0) return 0;
	if(mode==0||mode==1){
		printf("  Digite a chave de criptografia: ");
		scanf("%d", &key);
	}


    //video de leitura
    CvCapture* capture = cvCaptureFromAVI(in);
    //propriedades do video
    nFrames = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_COUNT);
    fps     = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FPS);
    frameH  = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT);
    frameW  = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH);
    codec = -1;
    //video final
    CvVideoWriter *writer = cvCreateVideoWriter(out,codec,
                            fps,cvSize(frameW,frameH),1);


    //PROCESSAMENTO E GRAVAÇÃO
    cvSetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES,0);
    for(int i = 0; i < nFrames-1; i++)
    {
        //inicializa imagem com white noise aleatório
        IplImage* keyImg = criarKey(key);
        IplImage* img;

		cvGrabFrame(capture);          // captura imagem
        img = cvRetrieveFrame(capture);  // recupera a imagem capturada

        //cvShowImage("Video Original",img); //mostra imagem original
        try
        {
            if(mode==0)
	    {
             //complementa a imagem
             cvNot(img, img);
             //soma dos frames do video com a imagem chave
             //operação de soma sem utilizar a saturação
             img = somaImg(img,keyImg,mode);
             //gira a imagem nos dois eixos
             cvFlip(img,img,-1);
             }
	     else if(mode==1)
	     {
             //gira a imagem nos dois eixos
	         cvFlip(img,img,-1);
             //soma dos frames do video com a imagem chave
             //operação de soma sem utilizar a saturação
             img = somaImg(img,keyImg,mode);
             cvNot(img, img);
             //complementa a imagem
	      }
              else if (mode == 2)
              {
                IplImage* img2 = cvCreateImage(cvSize(frameW,frameH),IPL_DEPTH_8U,3);
                //fechar pontos negros
                cvDilate(img,img, NULL, 1);
                cvErode(img,img, NULL, 1);
                //realçar bordas
                cvSobel(img,img2,1,1,3);
                cvAdd(img,img2,img);
                //retirar ruidos
                cvSmooth(img,img,CV_MEDIAN,5);
            }
            else if(mode== 3)
            {
                cvSmooth(img, img, CV_MEDIAN,5);
                //isolar bordas
                cvLaplace(img,img,3);
                //complementa para melhorar visualização
                cvNot(img,img);

                //engorda bordas com erosão

                cvErode(img,img, NULL,1);
                cvErode(img,img, NULL,1);


            }
            else break;
        }catch(cv::Exception e){continue;}


		//cvShowImage("Video modificado",img); //mostra imagem modificada
        cvWriteFrame(writer,img);      // grava imagem no video de saída
        cvWaitKey(1);           // espera 1ms
    }

    //LIBERAÇÃO DE RECURSOS

    cvReleaseCapture(&capture);
    cvReleaseVideoWriter(&writer);
    return 0;
}
