#include<opencv2/highgui/highgui.hpp>

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
         
      for( int x=0; x<img->width; x++ ) {
		 uchar cor = (ptr_img[3*x]+ptr_img[3*x+1]+ptr_img[3*x+2])/3;
         ptr_out[3*x] = cor;
         ptr_out[3*x+1] = cor;
         ptr_out[3*x+2] = cor;
      }
   }

   
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

