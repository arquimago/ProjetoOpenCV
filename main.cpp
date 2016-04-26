#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;


int main (int argc, char** argv){
    //inicializações
    CvCapture* capture = cvCaptureFromAVI("infile.avi"); //video

    //adquirir propriedades do video
    int isColor = 1;
    int fps = (int)cvGetCaptureProperty( capture, CV_CAP_PROP_FPS );
    int frameH  = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
    int frameW  = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
    int nFrames = (int)cvGetCaptureProperty(capture,  CV_CAP_PROP_FRAME_COUNT);
    //retornar um vídeo processado (também no formato AVI) como saída.
    CvVideoWriter *writer = cvCreateVideoWriter("out.avi",CV_FOURCC('P','I','M','1'),
                           fps,cvSize(frameW,frameH),isColor);

    // processamento
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

        //cvNot(img, img);
        //cvErode(img,img, NULL, 1 );
        //cvNot(img, img);
        //=
        //cvDilate(img,img, NULL, 1 );





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

DICAS CLAUDIO

Ah..... Massa!!!!

Você pode ao invés de modificar o tom dos pixels, embaralhá-los mudando suas posições (x, y) (e talvez incrementando com uma operação de soma subtração ou inversão). Isso é inversível... É só você pensar numa função que mapeie os pixels para outras posições e fazer a inversa depois.

Para esse caso onde o seu objetivo não é manter o bom aspecto e sim embaralhar. As operações de soma e subtração são úteis sim. Uma vez que se der overflow não é problema, já que seu objetivo é bugar a vida de quem tentar assistir (o vídeo criptografado).

Por via das dúvidas... Pergunte a Beatriz se ela consideraria o processamento de shuffle dos pixels.



DICAS BEATRIZ
(NÃO SERVE NO NOSSO CAS0)
gerar imagem com mod (tamanho de frames)
essa imagem sofrerá pouca alteração.
através dessa imagem, revertida por um processo simples,
será gerada nossa imagem que usaremos operações extras.

gerar imagem (aplicando processos mais complexos)
somar com imagem filme
processo inverso gerar e subtrair



complemento da erosão de a por b é igual ao complemento de a dilatado em espelho de b

(ida)pega imagem a, dilata em b, tira complemento
(vinda) pega imagem a' erode em b, tira complemento pelo espelho da máscara



operações inversas entre abertura e fechamento
complemento do fechamento de a por b é igual ao complemento de A aberto por espelho de b



procurar operação complemento opencv
espelhamento
*/
