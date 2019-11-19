void reka()
{
    int biale = 0, czarne = 0, a = 125, p = 0;
    double suma = 1, absolut = 1;
    int u = 0;
    while (1)
    {
        Mat frame;
        cap >> frame;
        cvtColor(frame, frame, CV_RGB2GRAY);
        warpPerspective(frame, frame, warp_mat, warp_dst.size());
        threshold(frame, frame, a, 255, 0);
        imshow("WINDOW", frame);
        namedWindow("WINDOW", CV_WINDOW_AUTOSIZE);
        createTrackbar("TrackbarName", "WINDOW", &a, 255);
        for (int i = 0; i < frame.rows; i++)
        {
            for (int j = 0; j < frame.cols; j++)
            {
                //if (p<100) printf("%d\n", frame.at<uchar>(i));
                if (frame.at<uchar>(p) == 255)
                    biale++;
                else
                    czarne++;
                p++;
            }
        }
        suma = biale + czarne;
        absolut = abs(biale - czarne);
        if (u == 0)
        {
            prog_reki = absolut / suma;
            u = 1;
        }
        cout << absolut / suma << endl
             << prog_reki << endl
             << endl;
        if (absolut / suma > prog_reki * 3 || absolut / suma < prog_reki / 3)
            cout << "!!!\n";
        waitKey(100);
        biale = czarne = p = 0;
    }
}
