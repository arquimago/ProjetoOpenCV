#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <time.h>
#include <stdio.h>


static int nFrames,fps,frameH,frameW;

static void troca(IplImage* n1, IplImage* n2)
{
    IplImage temp = *n1;
    *n1 = *n2;
    *n2 = temp;
    return;
}


static int aleatorio(int seed)
{
    int maxI =1000;
    int r[maxI];
    unsigned int retorno;
    int i;

    r[0] = seed;
    for (i=1; i<31; i++)
    {
        r[i] = (16807LL * r[i-1]) % 2147483647;
        if (r[i] < 0)
        {
            r[i] += 2147483647;
        }
    }
    for (i=31; i<34; i++)
    {
        r[i] = r[i-31];
    }
    for (i=34; i<344; i++)
    {
        r[i] = r[i-31] + r[i-3];
    }
    for (i=344; i<maxI; i++)
    {
        r[i] = r[i-31] + r[i-3];
        retorno = ((unsigned int)r[i]) >> 1;
    }
    return retorno;
}

static void filtro1(IplImage* img, IplImage* img2, int mask)
{
    //max
    for(int y=0; y < frameH; y++)
    {
        if(y-mask/2<=0) continue;
        uchar* ptr_img = (uchar*)(img->imageData + y * img->widthStep);
        uchar* ptr_img2 = (uchar*)(img2->imageData + y * img->widthStep);
        for(int x=0; x<frameW; x++)
        {
            if(x-mask/2<=0) continue;
            uchar maior[3];
            maior[0] = 0;
            maior[1] = 0;
            maior[2] = 0;
            int y_mask, x_mask;
            y_mask=y-mask/2;
            x_mask=x-mask/2;
            for(y_mask; y_mask<(y+mask/2); y_mask++)
            {
                for(x_mask; x_mask<(x+mask/2); x_mask++)
                {
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

static void filtro2(IplImage* img, IplImage* img2, int mask)
{
    //soma os pixels em volta (mascara)
    for(int y=0; y < frameH; y++)
    {
        if(y-mask/2<=0) continue;
        uchar* ptr_img = (uchar*)(img->imageData + y * img->widthStep);
        uchar* ptr_img2 = (uchar*)(img2->imageData + y * img->widthStep);
        for(int x=0; x<frameW; x++)
        {
            if(x-mask/2<=0) continue;
            uchar maior[3];
            maior[0] = 0;
            maior[1] = 0;
            maior[2] = 0;
            int y_mask, x_mask;
            y_mask=y-mask/2;
            x_mask=x-mask/2;
            for(y_mask; y_mask<(y+mask/2); y_mask++)
            {
                for(x_mask; x_mask<(x+mask/2); x_mask++)
                {
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

static void filtro3(IplImage* img, IplImage* img2,int mask)
{
    //min
    for(int y=0; y < frameH; y++)
    {
        if(y-mask/2<=0) continue;
        uchar* ptr_img = (uchar*)(img->imageData + y * img->widthStep);
        uchar* ptr_img2 = (uchar*)(img2->imageData + y * img->widthStep);
        for(int x=0; x<frameW; x++)
        {
            if(x-mask/2<=0) continue;
            uchar menor[3];
            menor[0] = 255;
            menor[1] = 255;
            menor[2] = 255;
            int y_mask, x_mask;
            y_mask=y-mask/2;
            x_mask=x-mask/2;
            for(y_mask; y_mask<(y+mask/2); y_mask++)
            {
                for(x_mask; x_mask<(x+mask/2); x_mask++)
                {
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

static void filtro4(IplImage* img, IplImage* img2)
{

}

static void filtro5(IplImage* img, IplImage* img2)
{

}

static void filtro6(IplImage* img, IplImage* img2)
{

}


static IplImage* criarKey (int key){

        IplImage* keyImg = cvCreateImage(cvSize(frameW,frameH),IPL_DEPTH_8U,3);
		for(int y = 0;y < keyImg->height;y++) {
			uchar* ptr_key = (uchar*) (keyImg->imageData + y * keyImg->widthStep);
			for(int x = 0;x < keyImg->width;x++){
                int nRand1 = aleatorio(key + (x * y) + 1)%256;
                int nRand2 = aleatorio(key + (x * y) + 2)%256;
                int nRand3 = aleatorio(key + (x * y) + 3)%256;
				//int nRand = aleatorio(key);
				ptr_key[3 * x]     = nRand1;
				ptr_key[3 * x + 1] = nRand2;
				ptr_key[3 * x + 2] = nRand3;
			}
		}
        return keyImg;
}


static IplImage* somaImg(IplImage* img,IplImage* keyImg){

        int temp1,temp2,temp3;
        for(int y=0; y < frameH; y++)
        {
            uchar* ptr_img = (uchar*)(img->imageData + y * img->widthStep);
            uchar* ptr_key = (uchar*)(keyImg->imageData + y * img->widthStep);
            for(int x=0; x<frameW; x++)
            {
                temp1 = ptr_img[3*x]   + ptr_key[3*x];
                temp2 = ptr_img[3*x+1] + ptr_key[3*x+1];
                temp3 = ptr_img[3*x+2] + ptr_key[3*x+2];

                /*
                if(temp1>255) temp1-=255;
                if(temp2>255) temp2-=255;
                if(temp3>255) temp3-=255;
                */
                ptr_img[3*x]   = temp1;
                ptr_img[3*x+1] = temp2;
                ptr_img[3*x+2] = temp3;

            }
        }

        return img;


}

static IplImage* subtracaoImg(IplImage* img,IplImage* keyImg){

        int temp1,temp2,temp3;
        for(int y=0; y < frameH; y++)
        {
            uchar* ptr_img = (uchar*)(img->imageData + y * img->widthStep);
            uchar* ptr_key = (uchar*)(keyImg->imageData + y * img->widthStep);
            for(int x=0; x<frameW; x++)
            {
                temp1 = ptr_img[3*x]   - ptr_key[3*x];
                temp2 = ptr_img[3*x+1] - ptr_key[3*x+1];
                temp3 = ptr_img[3*x+2] - ptr_key[3*x+2];

                /*
                if(temp1>255) temp1-=255;
                if(temp2>255) temp2-=255;
                if(temp3>255) temp3-=255;
                */
                ptr_img[3*x]   = temp1;
                ptr_img[3*x+1] = temp2;
                ptr_img[3*x+2] = temp3;

            }
        }

        return img;


}

