int tablica[8][8];
int tablica_clone[8][8];
string sciezka = "C:\\Users\\Kumputer\\Desktop\\szachy\\obrazki_spam\\";
Mat warp_mat(2, 4, CV_32FC1);
Mat warp_dst, warp_rotate_dst;
VideoCapture cap;
Mat board, board1;
double prog_reki = 0.2;
int prog = 100;

void overlayImage(const cv::Mat &background, const cv::Mat &foreground, cv::Mat &output, cv::Point2i location)
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

class Figure
{
public:
    Mat img;
    string dest;
    int stan;
    Figure(string a)
    {
        dest = a + ".png";
        img = imread(dest, -1);
        stan = 1;
    }
};

class Field
{
public:
    int x, y;
    Figure *figura;
    Field(int p, int q)
    {
        x = p;
        y = q;
    }
    void addfigure(string name)
    {
        figura = new Figure(name);
    }
};

void start(Field *board_tab[8][8])
{
    board_tab[3][0]->addfigure("krol_b");
    board_tab[3][7]->addfigure("krol_c");
    board_tab[4][0]->addfigure("krolowa_b");
    board_tab[4][7]->addfigure("krolowa_c");
    board_tab[0][0]->addfigure("wieza_b");
    board_tab[7][0]->addfigure("wieza_b");
    board_tab[0][7]->addfigure("wieza_c");
    board_tab[7][7]->addfigure("wieza_c");
    board_tab[1][0]->addfigure("kon_b");
    board_tab[6][0]->addfigure("kon_b");
    board_tab[1][7]->addfigure("kon_c");
    board_tab[6][7]->addfigure("kon_c");
    board_tab[2][0]->addfigure("laufer_b");
    board_tab[5][0]->addfigure("laufer_b");
    board_tab[2][7]->addfigure("laufer_c");
    board_tab[5][7]->addfigure("laufer_c");
    for (int i = 0; i < 8; i++)
    {
        board_tab[i][1]->addfigure("pion_b");
        board_tab[i][6]->addfigure("pion_c");
    }

    for (int j = 2; j < 6; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            board_tab[i][j]->addfigure("empty");
            board_tab[i][j]->figura->stan = 0;
        }
    }
}

void display(Field *board_tab[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            overlayImage(board, board_tab[i][j]->figura->img, board,
                         Point(board_tab[j][i]->x, board_tab[j][i]->y));
        }
    }
}

void play(Field *board_tab[8][8], int check)
{
    int a = 3, b = 3, c = 4, d = 4;
    Field *swap = new Field(30, 30);
    swap->addfigure("empty");
    swap->figura->stan = 0;

    system("cls");
    printf("Podaj 2 pola ktore chcesz zamienic miejscami (1-8 1-8, np. 5 5 1
           1) ");
        if (check != 0)
    {
        scanf("%d %d", &a, &b);
        scanf("%d %d", &c, &d);
        swap->figura = board_tab[a - 1][b - 1]->figura;
        board_tab[a - 1][b - 1]->figura = board_tab[c - 1][d - 1]->figura;
        board_tab[c - 1][d - 1]->figura = swap->figura;
        if (board_tab[a - 1][b - 1]->figura->stan == 1)
        {
            board_tab[a - 1][b - 1]->addfigure("empty");
            board_tab[a - 1][b - 1]->figura->stan = 0;
        }
    }
}

void wizualizacja()
{
    int check = 0;
    string Destination = "board1.png";
    board1 = imread(Destination, -1);
    board1.copyTo(board);
    Field *board_tab[8][8];
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board_tab[i][j] = new Field(15 + j * 100, 15 + i * 100);

            board_tab[i][j]->addfigure("empty");
        }
    }
    //wersja orginalna to z odkomentowanym startem i odwrotnym komentarzem
    while
        'a i for' a
            //start(board_tab); // nadawanie fieldom obrazkow
            start(board_tab);
    //getImage();
    /*dwa();
 if(prog!=0)
 {
 start(board_tab);
 prog=0;
 display(board_tab);
 namedWindow("Chess", CV_WINDOW_NORMAL);
 imshow("Chess",board);
 waitKey(0);
 }
 else
 {
 for(int i=0;i<8;i++)
 {
 for(int j=0;j<8;j++)
 {
 if(tablica[i][j]==tablica_clone[i][j]) cout<<"0 ";
 else cout<<"1 ";
 }
 cout<<endl;
 }
 display(board_tab);
 namedWindow("Chess", CV_WINDOW_NORMAL); 

 imshow("Chess",board);
 waitKey(0);
 }
 for(int i=0;i<8;i++)
 {
 for(int j=0;j<8;j++)
 {
 tablica_clone[i][j]=tablica[i][j];
 }
 }
 //imwrite(sciezka+"trzy.jpg", board);
 ustawianie pionkow, tam gdzie jest wiecej bialych niz prog
 for(int i=0;i<8;i++)
 {
 for(int j=0;j<8;j++)
 {
 if (tablica[j][i]>prog) board_tab[i][j]->addfigure("pion_b");
 }
 }*/
    while (1)
    {
        board1.copyTo(board);
        play(board_tab, check);
        display(board_tab);
        namedWindow("Chess", CV_WINDOW_NORMAL);
        imshow("Chess", board);
        waitKey(10);

        check = 1;
    }
}

int main()
{
    int skal = 0;
    cap.open(0); //do pracy ZAWSZE wlaczone
    while (1)
    {
        wizualizacja();
    }
}