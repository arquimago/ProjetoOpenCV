#include "conversor.cpp"

int main (int argc, char** argv)
{
    //INICIALIZAÇÕES
    //video inicial

    mode = 0;
    //1 CODIFICA
    //0 DECODIFICA
    char* in;
    char* out;
    if (mode==1){
        in  = "../infile.avi";
        out = "../out.avi";
    }
    else
    {
        in  = "../out.avi";
        out = "../decripted.avi";
    }


    CvCapture* capture = capture = cvCaptureFromAVI(in);

    //propriedades do video
    int key = 1024;
    nFrames = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_COUNT);
    fps     = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FPS);
    frameH  = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT);
    frameW  = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH);
    codec = cvGetCaptureProperty(capture,CV_CAP_PROP_FOURCC);
    //video final
    CvVideoWriter *writer = cvCreateVideoWriter(out,codec,
                            fps,cvSize(frameW,frameH),1);
    // imagem chave guardar o resultado da operação
    IplImage* keyImg = criarKey(key);
    IplImage* auxiliarImg = cvCreateImage(cvSize(frameW,frameH),IPL_DEPTH_8U,3);

    //tentar or ou and
    cvShowImage("imagem chave",keyImg);

    //printf("%d\n", nFrames);
    //PROCESSAMENTO E GRAVAÇÃO
    IplImage* img;

    cvSetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES,0);
    for(int i = 0; i < nFrames-1; i++)
    {
        cvGrabFrame(capture);          // captura imagem
        img = cvRetrieveFrame(capture);  // recupera a imagem capturada
        img = prepararImg(img);
        //gerar imagem aleatoria a cada frame

        //printf("Loop %d\n",i);

        if(i%2)
        {
            //filtro1(keyImg,auxiliarImg,3);
            //printf("par\n");
        }
        else
        {
            //filtro3(keyImg,auxiliarImg,3);
            //printf("impar\n");
        }

        cvShowImage("Video Original",img); //mostra imagem original
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
        cvSmooth(img, img, CV_GAUSSIAN, 9);
        cvLaplace(img,img,3);
        cvDilate(img,img,NULL,5);
        cvErode(img,img, NULL, 5 );
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
        cvFlip(img,img,-1);
        cvNot(img, img);
        */

        //soma dos frames do video com a imagem chave
        //operação de soma sem utilizar a saturação

        img = somaImg(img,keyImg,mode);

        //usar mais algumas operações reversíveis

        cvShowImage("Video modificado",img); //mostra imagem modificada
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
