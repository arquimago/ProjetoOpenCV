#include "conversor.cpp"


int main (int argc, char** argv)
{
    //INICIALIZAÇÕES
    //video inicial

    CvCapture* capture = cvCaptureFromAVI("../out.avi");
    //propriedades do video
    int key = 1024;
    nFrames = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_COUNT);
    fps     = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FPS);
    frameH  = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT);
    frameW  = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH);
    //video final
    CvVideoWriter *writer = cvCreateVideoWriter("../decripted.avi",CV_FOURCC('P','I','M','1'),
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

        img = subtracaoImg(img,keyImg);

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


