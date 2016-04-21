#include <opencv2/highgui/highgui.hpp>
using namespace cv;

int main (int argc, char** argv){
    //inicializa��es
    CvCapture* capture = cvCaptureFromAVI("infile.avi"); //video
    IplImage* frame; //frame do video

    //adquirir propriedades do video
    int isColor = 1;
    int fps = ( int )cvGetCaptureProperty( capture, CV_CAP_PROP_FPS );
    int frameH    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
    int frameW    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
    int nFrames = (int) cvGetCaptureProperty(capture,  CV_CAP_PROP_FRAME_COUNT);


    //retornar um v�deo processado (tamb�m no formato AVI) como sa�da.
    CvVideoWriter *writer = cvCreateVideoWriter("out.avi",CV_FOURCC('P','I','M','1'),
                           fps,cvSize(frameW,frameH),isColor);


    int key = 0;
    IplImage* img;
    for(int i=0;i<nFrames - 1;i++){
        cvGrabFrame(capture);          // capture a frame
        img=cvRetrieveFrame(capture);  // retrieve the captured frame
        cvShowImage("mainWin", img);
        key=cvWaitKey(20);           // wait 20 ms
        cvWriteFrame(writer,img);      // add the frame to the file

    }

    /*

     o seu programa deve aplicar um conjunto de m�todos de
    processamento de imagens em cada frame do v�deo.
    A aplica��o de cada m�todo deve obrigatoriamente modificar a imagem e ter relev�ncia no processo. O conjunto
    de m�todos aplicados deve resultar em um efeito coerente no v�deo final.

    4 m�todos diferentes devem ser utilizados



    aplicar, no m�nimo:
    - Tr�s operadores pontuais ou aritm�ticos;
    - Cinco filtros espaciais ou morfol�gicos.

    */

    /*
    #########################IDEIAS PARA O PROGRAMA#########################
    Algumas sequencias de opera��es desejaveis:


    processo com 4 ou mais filtros: esconder informa��o e extrair informa��o
    (um programa para esconder informa��o, embaralhando a imagem)
    (outro para extrair essa informa��o pelo processo inverso)
    (caso seja usado outro processo para tentar extrair informa��o, a imagem n�o deve ser entend�vel)


    usar opera��es �nicas e revers�veis
    (invers�o de cor, escurecimento, real�ar picos)
    sequencias de opera��es revers�veis
    (invers�o de cores->escurecimento)
    (real�ar picos -> invers�o de cores)

    http://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html

    alguns filtros
    //SUAVIZA��O cvSmooth(out, out, CV_GAUSSIAN, 9);


    ###########################################################################
    */

    //filtro1


    //filtro2


    //filtro3


    //filtro4


    //release the capture source
    cvReleaseCapture(&capture);
    cvReleaseVideoWriter(&writer);

    return 0;

}


