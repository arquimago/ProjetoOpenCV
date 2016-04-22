#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;


int main (int argc, char** argv){
    //inicializa��es
    CvCapture* capture = cvCaptureFromAVI("infile.avi"); //video

    //adquirir propriedades do video
    int isColor = 1;
    int fps = (int)cvGetCaptureProperty( capture, CV_CAP_PROP_FPS );
    int frameH  = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
    int frameW  = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
    int nFrames = (int)cvGetCaptureProperty(capture,  CV_CAP_PROP_FRAME_COUNT);
    //retornar um v�deo processado (tamb�m no formato AVI) como sa�da.
    CvVideoWriter *writer = cvCreateVideoWriter("out.avi",CV_FOURCC('P','I','M','1'),
                           fps,cvSize(frameW,frameH),isColor);

    // processamento
    IplImage* img;
    for(int i=0;i<nFrames - 1;i++){
        cvGrabFrame(capture);          // captura imagem
        img=cvRetrieveFrame(capture);  // recupera a imagem capturada
        cvShowImage("Video Original", img); //mostra imagem original
        /*
        o seu programa deve aplicar um conjunto de m�todos de
        processamento de imagens em cada frame do v�deo.
        A aplica��o de cada m�todo deve obrigatoriamente modificar a imagem e ter relev�ncia no processo. O conjunto
        de m�todos aplicados deve resultar em um efeito coerente no v�deo final.

        4 m�todos diferentes devem ser utilizados

        aplicar, no m�nimo:
        - Tr�s operadores pontuais ou aritm�ticos;
        - Cinco filtros espaciais ou morfol�gicos.



        processo com 4 ou mais filtros: esconder informa��o e extrair informa��o
        (um programa para esconder informa��o, embaralhando a imagem)
        (outro para extrair essa informa��o pelo processo inverso)
        (caso seja usado outro processo para tentar extrair informa��o, a imagem n�o deve ser entend�vel)

        alguns filtros
        http://docs.opencv.org/2.4/modules/imgproc/doc/miscellaneous_transformations.html
        http://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html
        http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html

        cvSobel(img, img, 1, 1, 3 );
        cvSmooth(img, img, CV_GAUSSIAN, 9);
        cvLaplace(img, img, 3 );
        cvDilate(img,img, NULL, 5 );
        cvErode(img,img, NULL, 5 );
        cvNot(img, img);
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
        (mais em http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html)
        */



        cvShowImage("Video modificado", img); //mostra imagem modificada

        cvWriteFrame(writer,img);      // grava imagem no video de sa�da
        cvWaitKey(1);           // espera 1ms
    }

    //liberar recursos
    cvReleaseCapture(&capture);
    cvReleaseVideoWriter(&writer);
    return 0;

}


