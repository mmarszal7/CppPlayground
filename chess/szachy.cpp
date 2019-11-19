#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace cv;
using namespace std;

int tablica[8][8];
string sciezka = "C:\\Users\\Kumputer\\Desktop\\szachy\\obrazki_spam\\";
Mat warp_mat(2, 4, CV_32FC1);
Mat warp_dst, warp_rotate_dst;
VideoCapture cap;
Mat board, board1;
double prog_reki = 0.2;

void overlayImage(const cv::Mat &background, const cv::Mat &foreground,
                  cv::Mat &output, cv::Point2i location)
{
    background.copyTo(output);
    // start at the row indicated by location, or at row 0 if location.y is
    negative.for (int y = std::max(location.y, 0); y < background.rows; ++y)
    {

        int fY = y - location.y; // because of the translation
                                 // we are done of we have
        processed all rows of the foreground image.if (fY >= foreground.rows) break;
        // start at the column indicated by location,
        // or at column 0 if location.x is negative.
        for (int x = std::max(location.x, 0); x < background.cols; ++x)
        {
            int fX = x - location.x; // because of the translation.
                                     // we are done with
            this row if the column is outside of the foreground image.if (fX >= foreground.cols) break;
            // determine the opacity of the foregrond pixel, using its
            fourth(alpha) channel.double opacity =
                ((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3]) / 255.;
            // and now combine the background and foreground pixel, using
            the opacity,
                // but only if opacity > 0.
                for (int c = 0; opacity > 0 && c < output.channels(); ++c)
            {
                unsigned char foregroundPx =
                    foreground.data[fY * foreground.step + fX * foreground.channels() + c];

                unsigned char backgroundPx =
                    background.data[y * background.step + x * background.channels() + c];
                output.data[y * output.step + output.channels() * x + c] =
                    backgroundPx * (1. - opacity) + foregroundPx *
                                                        opacity;
            }
        }
    }
}

void getImage()
{
    string nazwa2;
    string numer;
    string caly;
    int k = 0;
    char ok = 0;
    cout << endl
         << "Ustaw figury i nacisnij dowolny klawisz.";
    cin >> ok;
    Mat frame;
    cap >> frame;
    cap >> frame;
    cvtColor(frame, frame, CV_BGR2GRAY);
    warpPerspective(frame, warp_dst, warp_mat, warp_dst.size());
    imshow("Wynik", warp_dst);
    waitKey(3000);
    destroyWindow("Wynik");
    ostringstream ss;
    nazwa2 = ".jpg";
    ss << k;
    numer = ss.str();
    caly = sciezka + numer + nazwa2;
    cout << caly << endl;

    imwrite(caly, warp_dst);
    k = k + 1;
}

void dwa()
{
    Mat obraz, obraz_szare, obraz_bin;
    //String Destination = "D://kupa3//36.jpg";
    String Destination = sciezka + "0.jpg";
    obraz = imread(Destination);
    cvtColor(obraz, obraz_szare, CV_BGR2GRAY);
    Mat kernel2 = Mat::zeros(3, 3, CV_32F);
    // assigns kernel values
    kernel2.at<float>(1, 1) = 5.0;
    kernel2.at<float>(0, 1) = -1.0;
    kernel2.at<float>(2, 1) = -1.0;
    kernel2.at<float>(1, 0) = -1.0;
    kernel2.at<float>(1, 2) = -1.0;
    //filter the image
    //filter2D(obraz_szare, obraz_szare, -1, kernel2);
    //imshow("wejscie", obraz_szare);
    //waitKey(3000);
    //destroyWindow("wejscie");
    GaussianBlur(obraz_szare, obraz_szare, Size(3, 3), 2, 2);
    adaptiveThreshold(obraz_szare, obraz_szare, 255, THRESH_BINARY, 0, 3, 0);
    //threshold(obraz_szare, obraz_szare, 180, 255, 0);
    Mat kernel = Mat::ones(3, 3, CV_32F);
    morphologyEx(obraz_szare, obraz_szare, 2, kernel);
    //imwrite(sciezka+"01.jpg", obraz_szare);

    //namedWindow("win2", CV_WINDOW_AUTOSIZE);
    imshow("win2", obraz_szare);
    imwrite(sciezka + "dwa.jpg", obraz_szare);
    //waitKey(0);
    waitKey(3000);
    destroyWindow("win2");
    // trzy
    int biale = 0, a = 0;
    Mat OurImage, OurImage2, result, Image;
    OurImage = obraz_szare;
    OurImage2 = OurImage.clone();
    //cvtColor(OurImage, OurImage, CV_RGB2GRAY);
    Mat obraz_roi;
    int wiersz, kolumna;
    int min = 3000, max = 0;
    float wynik = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            obraz_roi = OurImage(Rect(8 + j * 50, 8 + i * 50, 34, 34));
            for (int ii = 0; ii < obraz_roi.rows; ii++)
            {
                for (int jj = 0; jj < obraz_roi.cols; jj++)
                {
                    //printf("%d\n", OurImage.at<uchar>(i));
                    if (obraz_roi.at<uchar>(ii, jj) == 255)
                        biale++;
                }
            }
            /*Image = OurImage2.clone();
 rectangle(Image, Point(8 + j * 50, 8+ i * 50), Point(45 + j *
50, 45 + i * 50), Scalar(0, 0, 255), 3, 8, 0); 

 imshow("Obrazek", obraz_roi);
 imshow("Obrazek_caly", Image);
 waitKey(50);
 printf("%3d ", biale);*/
            tablica[i][j] = biale;
            if (biale != 0)
            {
                if (biale > max)
                    max = biale;
                if (biale < min)
                    min = biale;
            }
            biale = 0;
        }
        //printf(" \n");
    }
    int prog;
    cout << endl
         << "To jest max: " << max << ". Teraz ustal prog";
    cin >> prog;
    printf(" \n");
    printf(" \n");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (tablica[i][j] < prog)
                tablica[i][j] = 0;
            else
                tablica[i][j] = 1;
            cout << tablica[i][j] << " ";
        }
        cout << endl;
    }
    //cout<<endl<<min<<endl<<max;
    waitKey(1000);
    destroyWindow("wejscie");
}

int main()
{
    int skal = 0;
    cap.open(0); //do pracy ZAWSZE wlaczone

    skalowanie();
    getImage();
    system("cls");
    cout << "Czy skalowanie przebieglo poprawnie?? (1 jesli tak)";
    cin >> skal;
    if (skal != 1)
    {
        skalowanie();
        getImage();
    }

    dwa();
    waitKey(10000);
}