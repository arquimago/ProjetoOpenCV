#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <time.h>


#include <stdio.h>

int nFrames,fps,frameH,frameW;

void troca(IplImage* n1, IplImage* n2){
	IplImage temp = *n1;
	*n1 = *n2;
	*n2 = temp;
	return;
}


int aleatorio(int seed) {
	int maxI =1000;
	int r[maxI];
	unsigned int retorno;
	int i;

	r[0] = seed;
	for (i=1; i<31; i++) {
		r[i] = (16807LL * r[i-1]) % 2147483647;
		if (r[i] < 0) {
			r[i] += 2147483647;
		}
	}
	for (i=31; i<34; i++) {
		r[i] = r[i-31];
	}
	for (i=34; i<344; i++) {
		r[i] = r[i-31] + r[i-3];
	}
	for (i=344; i<maxI; i++) {
		r[i] = r[i-31] + r[i-3];
		retorno = ((unsigned int)r[i]) >> 1;
	}
	return retorno;
}

void filtro1(IplImage* img, IplImage* img2, int mask){
	//max
	for(int y=0;y < frameH;y++) {
        if(y-mask/2<=0) continue;
		uchar* ptr_img = (uchar*)(img->imageData + y * img->widthStep);
        uchar* ptr_img2 = (uchar*)(img2->imageData + y * img->widthStep);
		for(int x=0; x<frameW; x++) {
			if(x-mask/2<=0) continue;
			uchar maior[3];
			maior[0] = 0;
			maior[1] = 0;
			maior[2] = 0;
            int y_mask, x_mask;
			y_mask=y-mask/2;
			x_mask=x-mask/2;
			for(y_mask; y_mask<(y+mask/2); y_mask++){
				for(x_mask; x_mask<(x+mask/2); x_mask++){
					//encontrar o maximo
					if(ptr_img[3*x_mask] > maior[0]) maior[0] = ptr_img[3*x_mask];
					if(ptr_img[3*x_mask+1] > maior[1]) maior[1] = ptr_img[3*x_mask+1];
					if(ptr_img[3*x_mask+2] > maior[2]) maior[2] = ptr_img[3*x_mask+2];	
				}
			}
			ptr_img2[3*x]=maior[0];
			ptr_img2[3*x+1]=maior[1];
			ptr_img2[3*x+2]=maior[2];
        }
    }
	troca(img,img2);
}

void filtro2(IplImage* img, IplImage* img2, int mask){
	//soma os pixels em volta (mascara)
	for(int y=0;y < frameH;y++) {
        if(y-mask/2<=0) continue;
		uchar* ptr_img = (uchar*)(img->imageData + y * img->widthStep);
        uchar* ptr_img2 = (uchar*)(img2->imageData + y * img->widthStep);
		for(int x=0; x<frameW; x++) {
			if(x-mask/2<=0) continue;
			uchar maior[3];
			maior[0] = 0;
			maior[1] = 0;
			maior[2] = 0;
            int y_mask, x_mask;
			y_mask=y-mask/2;
			x_mask=x-mask/2;
			for(y_mask; y_mask<(y+mask/2); y_mask++){
				for(x_mask; x_mask<(x+mask/2); x_mask++){
					//encontrar o maximo
					maior[0]+= ptr_img[3*x_mask];
					maior[1]+= ptr_img[3*x_mask+1];
					maior[2]+= ptr_img[3*x_mask+2];	
				}
			}
			ptr_img2[3*x]=maior[0];
			ptr_img2[3*x+1]=maior[1];
			ptr_img2[3*x+2]=maior[2];
        }
    }
	troca(img,img2);
}

void filtro3(IplImage* img, IplImage* img2,int mask){
	//min
	for(int y=0;y < frameH;y++) {
        if(y-mask/2<=0) continue;
		uchar* ptr_img = (uchar*)(img->imageData + y * img->widthStep);
        uchar* ptr_img2 = (uchar*)(img2->imageData + y * img->widthStep);
		for(int x=0; x<frameW; x++) {
			if(x-mask/2<=0) continue;
			uchar menor[3];
			menor[0] = 255;
			menor[1] = 255;
			menor[2] = 255;
            int y_mask, x_mask;
			y_mask=y-mask/2;
			x_mask=x-mask/2;
			for(y_mask; y_mask<(y+mask/2); y_mask++){
				for(x_mask; x_mask<(x+mask/2); x_mask++){
					//encontrar o minimo
					if(ptr_img[3*x_mask] < menor[0]) menor[0] = ptr_img[3*x_mask];
					if(ptr_img[3*x_mask+1] < menor[1]) menor[1] = ptr_img[3*x_mask+1];
					if(ptr_img[3*x_mask+2] < menor[2]) menor[2] = ptr_img[3*x_mask+2];	
				}
			}
			ptr_img2[3*x]=menor[0];
			ptr_img2[3*x+1]=menor[1];
			ptr_img2[3*x+2]=menor[2];
        }
    }
	troca(img,img2);
}

void filtro4(IplImage* img, IplImage* img2){
	
}

void filtro5(IplImage* img, IplImage* img2){
	
}

void filtro6(IplImage* img, IplImage* img2){
	
}


int main (int argc, char** argv){
    //INICIALIZAÇÕES
    //video inicial
	
    CvCapture* capture = cvCaptureFromAVI("infile.avi");
    //propriedades do video
    int key = 1024;
    nFrames = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_COUNT);
    fps     = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FPS);
    frameH  = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT);
    frameW  = (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH);
    srand(key);

    //video final
    CvVideoWriter *writer = cvCreateVideoWriter("out.avi",CV_FOURCC('P','I','M','1'),
                           fps,cvSize(frameW,frameH),1);
    // imagem chave guardar o resultado da operação
    //int fator = 100;
    //frameW/5/2;
    //100 é um bom valor
    IplImage* keyImg = cvCreateImage(cvSize(frameW,frameH),IPL_DEPTH_8U,3);
	IplImage* auxiliarImg = cvCreateImage(cvSize(frameW,frameH),IPL_DEPTH_8U,3);
    /*for(int y = 0;y < keyImg->height;y++) {
        uchar* ptr_key = (uchar*) (keyImg->imageData + y * keyImg->widthStep);
        for(int x = 0;x < keyImg->width;x++){
             int nRand = aleatorio(key + (x * y))%256;
             ptr_key[3 * x]     = nRand;
             ptr_key[3 * x + 1] = nRand;
             ptr_key[3 * x + 2] = nRand;
        }
    }*/

    //tentar or ou and
    //cvShowImage("imagem chave",keyImg);

	printf("%d\n", nFrames);
    //PROCESSAMENTO E GRAVAÇÃO
    IplImage* img;
    cvSetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES,0);
    for(int i = 0;i < nFrames-1;i++){
        cvGrabFrame(capture);          // captura imagem
        img = cvRetrieveFrame(capture);  // recupera a imagem capturada
        
		//gerar imagem aleatoria a cada frame
		
		printf("Loop %d\n",i);
		for(int y = 0;y < keyImg->height;y++) {
			uchar* ptr_key = (uchar*) (keyImg->imageData + y * keyImg->widthStep);
			for(int x = 0;x < keyImg->width;x++){
				int nRand1 = rand()%256;
				int nRand2 = rand()%256;
				int nRand3 = rand()%256;
				//int nRand = aleatorio(key);
				ptr_key[3 * x]     = nRand1;
				ptr_key[3 * x + 1] = nRand2;
				ptr_key[3 * x + 2] = nRand3;
			}
		}
		
		
		
		if(i%2){
			//filtro1(keyImg,auxiliarImg,3);
			printf("par\n");
		} else {
			//filtro3(keyImg,auxiliarImg,3);
			printf("impar\n");
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
        int temp1,temp2,temp3;
		for(int y=0;y < frameH;y++) {
            uchar* ptr_img = (uchar*)(img->imageData + y * img->widthStep);
            uchar* ptr_key = (uchar*)(keyImg->imageData + y * img->widthStep);
            for(int x=0; x<frameW; x++) {
                temp1 = ptr_img[3*x]   + ptr_key[3*x];
				temp2 = ptr_img[3*x+1] + ptr_key[3*x+1];
				temp3 = ptr_img[3*x+2] + ptr_key[3*x+2];
				
				if(temp1>255) temp1-=255;
				if(temp2>255) temp2-=255;
				if(temp3>255) temp3-=255;
				
				ptr_img[3*x]   = temp1;
                ptr_img[3*x+1] = temp2;
                ptr_img[3*x+2] = temp3;
            }
        }
		
		//cvLaplace(img,img,3);

        //usar mais algumas operações reversíveis

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
gerar imagem listras brancas e pretas

através dessa imagem,
será gerada uma imagem por:
processamento a e somada a frames de numero par
processamento b e somada a frames de numero impar

processo inverso gerar e subtrair.

procurar
espelhamento
shuffle

DICAS CLAUDIO

Ah..... Massa!!!!
Você pode ao invés de modificar o tom dos pixels, embaralhá-los mudando suas posições (x, y) (e talvez incrementando com uma operação de soma subtração ou inversão). Isso é inversível...
É só você pensar numa função que mapeie os pixels para outras posições e fazer a inversa depois.
Para esse caso onde o seu objetivo não é manter o bom aspecto e sim embaralhar.
As operações de soma e subtração são úteis sim. Uma vez que se der overflow não é problema, já que seu objetivo é bugar a vida de quem tentar assistir (o vídeo criptografado).
Por via das dúvidas... Pergunte a Beatriz se ela consideraria o processamento de shuffle dos pixels.
*/
