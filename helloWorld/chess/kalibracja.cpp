void skalowanie()
{
    int gotowy = 0;
    bool patternfound = 0;
    char znak;
    float skala_obrazowania = 2; // 1- 800 pixeli 2- 400 pixeli itd.
    float roxnica_x;
    float roxnica_y;
    Point2f srcTri[4];
    Point2f dstTri[4];
    Size boardsize(7, 7);
    vector<Point2f> centers;
    //VideoCapture cap;
    Mat frame, frame2, obraz;
    while (patternfound == 0)
    {
        system("cls");
        cout << "Czy szachownica jest gotowa do kalibracji?\n"
             << endl;
        cout << "Jesli tak nacisnij 'y'." << endl;
        cin >> znak;
        if (znak == 'y')
        {
            cap >> frame2;
            cap >> frame2;
            frame = frame2.clone();
            cvtColor(frame, frame, CV_BGR2GRAY);
            patternfound = findChessboardCorners(frame, boardsize,
                                                 centers);
        }

        if (patternfound == 1)
        {
            roxnica_x = (centers[6].x - centers[0].x) / 6;
            roxnica_y = (centers[42].y - centers[0].y) / 6;
            warp_dst = Mat::zeros(800 / skala_obrazowania, 800 / skala_obrazowania, frame.type());
            /// Set your 3 points to calculate the Affine Transform
            srcTri[0] = Point2f(centers[0].x - roxnica_x, centers[0].y -
                                                              roxnica_y);
            srcTri[1] = Point2f(centers[6].x + roxnica_x, centers[6].y -
                                                              roxnica_y);
            srcTri[2] = Point2f(centers[42].x - roxnica_x, centers[42].y + roxnica_y);
            srcTri[3] = Point2f(centers[48].x + roxnica_x, centers[48].y + roxnica_y);
            dstTri[0] = Point2f(0, 0);
            dstTri[1] = Point2f(800 / skala_obrazowania, 0);
            dstTri[2] = Point2f(0, 800 / skala_obrazowania);
            dstTri[3] = Point2f(800 / skala_obrazowania, 800 /
                                                             skala_obrazowania);
            /// Get the Affine Transform
            warp_mat = getPerspectiveTransform(srcTri, dstTri);
            system("cls");
            cout << endl
                 << "Wyskalowane!";
        }
    }
}