// OVERFLOW DE CORES
//saturation
//http://answers.opencv.org/question/13769/adding-matrices-without-saturation/
//por algum motivo que não descobri, ao somar valores muito baixos ou muito altos ,a imagem não se altera
//imagem estoura e volta para a mesma posição com 255 e não muda ao somar com 0
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <limits.h>
using namespace cv;
using namespace std;

int main (int argc, char** argv){
    //inicializações
    //video inicial
    CvCapture* capture = cvCaptureFromAVI("infile.avi");
    //propriedades do video
    int nFrames = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
    int fps     = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
    int frameH  = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
    int frameW  = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
    //video final
    CvVideoWriter *writer = cvCreateVideoWriter("out.avi",CV_FOURCC('P','I','M','1'),
                           fps,cvSize(frameW,frameH),1);


    // imagem chave
    //Imagem pra guardar o resultado da operação
    int fator = 35;
    IplImage* key = cvCreateImage(cvSize(frameW,frameH), IPL_DEPTH_8U, 3);
    for( int y=0; y < key->height; y++ ) {
        uchar* ptr_key = (uchar*) (key->imageData + y * key->widthStep);

        for( int x=0; x < key->width; x++ ) {
             ptr_key[3*x]   = 0 +(x * fator);
             ptr_key[3*x+1] = 0 +(x * fator);
             ptr_key[3*x+2] = 0 +(x * fator);
        }
    }
    cvShowImage( "imagem chave", key );



    //escrita e processamento
    IplImage* img;
    cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, 0);
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



        processo com 4 ou mais filtros: esconder informação e extrair informação
        (um programa para esconder informação, embaralhando a imagem)
        (outro para extrair essa informação pelo processo inverso)
        (caso seja usado outro processo para tentar extrair informação, a imagem não deve ser entendível)

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

        //SOMA SEM SATURAÇÃO
        for( int y=0; y < frameH; y++ ) {
            uchar* ptr_img = (uchar*) (img->imageData + y * img->widthStep) ;
            uchar* ptr_key = (uchar*) (key->imageData + y * img->widthStep);

            for( int x=0; x<frameW; x++ ) {
                ptr_img[3*x]   = ptr_img[3*x] + ptr_key[3*x];
                ptr_img[3*x+1] = ptr_img[3*x+1] + ptr_key[3*x+1];
                ptr_img[3*x+2] = ptr_img[3*x+2] + ptr_key[3*x+2];
            }
        }


        cvShowImage("Video modificado", img); //mostra imagem modificada
        cvWriteFrame(writer,img);      // grava imagem no video de saída
        cvWaitKey(1);           // espera 1ms
       }

    //liberar recursos
    cvReleaseCapture(&capture);
    cvReleaseVideoWriter(&writer);


    return 0;

}

/*

gerar imagem listras brancas e pretas

através dessa imagem,
será gerada uma imagem por:
processamento a e somada a frames de numero par
processamento b e somada a frames de numero impar



gerar imagem (aplicando processos mais complexos)
somar com imagem filme
processo inverso gerar e subtrair

procurar
espelhamento




DICAS CLAUDIO

Ah..... Massa!!!!

Você pode ao invés de modificar o tom dos pixels, embaralhá-los mudando suas posições (x, y) (e talvez incrementando com uma operação de soma subtração ou inversão). Isso é inversível... É só você pensar numa função que mapeie os pixels para outras posições e fazer a inversa depois.

Para esse caso onde o seu objetivo não é manter o bom aspecto e sim embaralhar. As operações de soma e subtração são úteis sim. Uma vez que se der overflow não é problema, já que seu objetivo é bugar a vida de quem tentar assistir (o vídeo criptografado).

Por via das dúvidas... Pergunte a Beatriz se ela consideraria o processamento de shuffle dos pixels.

*/
