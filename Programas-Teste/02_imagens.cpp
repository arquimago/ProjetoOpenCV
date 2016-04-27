#include<opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <stdlib.h>
#include <stdio.h>
using namespace cv;

int main()
{

   IplImage* img = cvLoadImage( "fruits.jpg" );

   //Imagem pra guardar o resultado da operação
   IplImage* out = cvCreateImage(
                   cvGetSize(img), IPL_DEPTH_8U, 3);


    //cria duas janelas
   //CV_WINDOW_AUTOSIZE: janela se expande para mostrar imagem em tamanho real
   //0: cria janela com tamanho fixo
   cvNamedWindow( "Imagem Original", CV_WINDOW_AUTOSIZE);
   cvNamedWindow( "Imagem de Saida", CV_WINDOW_AUTOSIZE);


   for( int y=0; y<img->height; y++ ) {
      uchar* ptr_img = (uchar*) (
         img->imageData + y * img->widthStep);
      uchar* ptr_out = (uchar*) (
         out->imageData + y * out->widthStep);


	int fator = 35.0;
    for( int x=0; x<img->width; x++ ) {
		 ptr_img[3*x] = ptr_img[3*x] + (x * fator);
         ptr_img[3*x+1] =ptr_img[3*x+1] + (x * fator);
         ptr_img[3*x+2] = ptr_img[3*x+2] +(x * fator);
      }


	for( int x=0; x<img->width; x++ ) {
		 ptr_out[3*x] = ptr_img[3*x] - (x * fator);
         ptr_out[3*x+1] = ptr_img[3*x+1] - (x * fator);
         ptr_out[3*x+2] = ptr_img[3*x+2] - (x * fator);
      }
   }
   //sobel cvSobel(img, out, 1, 1, 3 );
   //suavização cvSmooth(img, out, CV_GAUSSIAN, 9);
   //exibe a imagem img na janela
   cvShowImage( "Imagem Original", img );

   //exibe a imagem out na janela
   cvShowImage( "Imagem de Saida", out );

   //faz com que o programa espere por um evento do teclado
   cvWaitKey(0);

   //destroi janelas
   cvDestroyWindow( "Imagem Original");
   cvDestroyWindow( "Imagem de Saida");

   //destroi imagem
   cvReleaseImage( &img );
   cvReleaseImage( &out );
   return 1;
}

