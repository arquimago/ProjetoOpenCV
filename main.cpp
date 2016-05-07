#include "conversor.cpp"

int main (int argc, char** argv)
{
    //INICIALIZAÇÕES
    //video inicial

    mode = 2;
    //0 CODIFICA
    //1 DECODIFICA
	//2 MELHORA
    char* in;
    char* out;

    if (mode==0||mode==2){
        in  = "infile.avi";
        out = "out.avi";
    }
    else
    {
        in  = "out.avi";
        out = "decripted.avi";
    }


    //video final
    CvCapture* capture = cvCaptureFromAVI(in);
    //propriedades do video
    int key = 1024;
    nFrames = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_COUNT);
    fps     = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FPS);
    frameH  = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT);
    frameW  = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH);
    codec = -1;

    CvVideoWriter *writer = cvCreateVideoWriter(out,codec,
                            fps,cvSize(frameW,frameH),1);


    //PROCESSAMENTO E GRAVAÇÃO
    IplImage* img,img2;
	
	img2 = cvCreateImage(cvSize(frameW,frameH),IPL_DEPTH_8U,3);
	
    cvSetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES,0);
    for(int i = 0; i < nFrames-1; i++)
    {
        IplImage* keyImg = criarKey(key);
		
		cvGrabFrame(capture);          // captura imagem
        img = cvRetrieveFrame(capture);  // recupera a imagem capturada


        if(mode==1||mode==0)
        {
            //soma dos frames do video com a imagem chave
			//operação de soma sem utilizar a saturação
			cvNot(img, img);
			img = somaImg(img,keyImg,mode);
			cvFlip(img,img,-1);
			
        }
        else if (mode == 2)
        {
			cvSmooth(img, img, CV_MEDIAN, 5);
			
			cvSobel(img,img2,1,1,3);
			img = somaImg(img,img2,1);
						
			cvLaplace(img,img2,3);
			img = somaImg(img,img2,1);
			
			//Abertura
			cvErode(img,img, NULL, 5 );
			cvDilate(img,img,NULL,5);
			
			//Fechamento
			cvDilate(img,img,NULL,5);
			cvErode(img,img, NULL, 5);
			
        }
		else
		{
			break;
		}

        //cvShowImage("Video Original",img); //mostra imagem original
        /*
        o seu programa deve aplicar um conjunto de métodos de
        processamento de imagens em cada frame do vídeo.
        A aplicação de cada método deve obrigatoriamente modificar a imagem e ter relevância no processo. O conjunto
        de métodos aplicados deve resultar em um efeito coerente no vídeo final.

        4 métodos diferentes devem ser utilizados

        aplicar, no mínimo:
        - Três operadores pontuais ou aritméticos;
        - Cinco filtros espaciais ou morfológicos.



        processo com 4 ou mais filtros: esconder informação e extrair informação
        (um programa para esconder informação, embaralhando a imagem)
        (outro para extrair essa informação pelo processo inverso)
        (caso seja usado outro processo para tentar extrair informação, a imagem não deve ser entendível)

        algumas operações
        http://docs.opencv.org/2.4/modules/imgproc/doc/miscellaneous_transformations.html
        http://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html
        http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html
        http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html

        cvSobel(img,img,1,1,3);
		cvLaplace(img,img,3);
        cvDilate(img,img,NULL,5);
        cvErode(img,img, NULL, 5 );
		cvFlip(img,img,-1);
        cvNot(img, img);
		cvSmooth(img, img, CV_MEDIAN, 5);
        
        cvCvtColor(img, img, CV_BGR2Luv);
        cvThreshold(img,img, 30, 700, 1);
        cvAbsDiff(img, img, img);
        cvAdd(img,img, img);
        cvAnd(img,img,img);
        cvOr(img,img,img);
        cvXor(img,img,img);
        cvConvertScaleAbs(img,img,3,4);
        cvDiv(img,img,img,1);
        cvMul(img,img,img,1);

        reversíveis
        
        */

        
		//cvShowImage("Video modificado",img); //mostra imagem modificada
        cvWriteFrame(writer,img);      // grava imagem no video de saída
        cvWaitKey(1);           // espera 1ms
    }

    //LIBERAÇÃO DE RECURSOS

    cvReleaseCapture(&capture);
    cvReleaseVideoWriter(&writer);
    return 0;
}
/*
procurar
espelhamento
shuffle
*/
