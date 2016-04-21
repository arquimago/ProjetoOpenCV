#include <opencv2/highgui/highgui.hpp>
using namespace cv;

int main (int argc, char** argv){
    //inicializações
    CvCapture* capture = cvCaptureFromAVI("infile.avi"); //video
    IplImage* frame; //frame do video
    //adquirir propriedades do video
    int isColor = 1;
    int fps = ( int )cvGetCaptureProperty( capture, CV_CAP_PROP_FPS );
    int frameH    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
    int frameW    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
    int nFrames = (int) cvGetCaptureProperty(capture,  CV_CAP_PROP_FRAME_COUNT);
    //retornar um vídeo processado (também no formato AVI) como saída.
    CvVideoWriter *writer = cvCreateVideoWriter("out.avi",CV_FOURCC('P','I','M','1'),
                           fps,cvSize(frameW,frameH),isColor);

    // processamento
    int key = 0;
    IplImage* img;
    for(int i=0;i<nFrames - 1;i++){
        cvGrabFrame(capture);          // captura imagem
        img=cvRetrieveFrame(capture);  // recupera a imagem capturada
        cvShowImage("Video Original", img); //mostra imagem original
        /*


        o seu programa deve aplicar um conjunto de métodos de
        processamento de imagens em cada frame do vídeo.
        A aplicação de cada método deve obrigatoriamente modificar a imagem e ter relevância no processo. O conjunto
        de métodos aplicados deve resultar em um efeito coerente no vídeo final.

        4 métodos diferentes devem ser utilizados



        aplicar, no mínimo:
        - Três operadores pontuais ou aritméticos;
        - Cinco filtros espaciais ou morfológicos.




        #########################IDEIAS PARA O PROGRAMA#########################
        Algumas sequencias de operações desejaveis:


        processo com 4 ou mais filtros: esconder informação e extrair informação
        (um programa para esconder informação, embaralhando a imagem)
        (outro para extrair essa informação pelo processo inverso)
        (caso seja usado outro processo para tentar extrair informação, a imagem não deve ser entendível)


        usar operações únicas e reversíveis
        (inversão de cor, escurecimento, realçar picos)
        sequencias de operações reversíveis
        (inversão de cores->escurecimento)
        (realçar picos -> inversão de cores)

        http://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html

        alguns filtros
        //SUAVIZAÇÃO cvSmooth(out, out, CV_GAUSSIAN, 9);


        ###########################################################################


        */
        //alguns filtros
        //cvSobel(img, img, 1, 1, 3 );
        //cvSmooth(img, img, CV_GAUSSIAN, 9);
        //cvLaplace(img, img, 3 );
        //cvDilate(img,img, NULL, 5 );
        //cvErode(img,img, NULL, 5 );
        //cvShowImage("Video modificado", img); //mostra imagem modificada


        cvWriteFrame(writer,img);      // grava imagem no video de saída
        cvWaitKey(1);           // espera 1ms
    }



    //release the capture source
    cvReleaseCapture(&capture);
    cvReleaseVideoWriter(&writer);

    return 0;

}


