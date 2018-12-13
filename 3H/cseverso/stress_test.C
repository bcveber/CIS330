#include <PNMreader.h>
#include <PNMwriter.h>
#include <filter.h>
#include <logging.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using std::cerr;
using std::endl;
using std::ofstream;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <username>" << endl;
        exit(EXIT_FAILURE);
    }

    char event[1024];
    sprintf(event, "Entered program from %s\n", argv[1]);
    Logger::LogEvent(event);



    /* ================================ */
    /* START STUDENT MODIFIABLE SECTION */
    /* ================================ */

    /* you may want one or more readers! */
    PNMreader reader("../images/hank.pnm");  // note: filename must be "../images/image_name.pnm"
    Shrinker shrinkers[6];
    Color blacksq(10, 15, 0, 0, 0);
    Color blackln(50, 15, 0, 0, 0);
    LRCombine lrs[6];
    TBCombine tbs[4];
    //Color 893, 672, 255, 215, 0);




    shrinkers[0].SetInput(reader.GetOutput());
    for(int i = 1; i < 5; i++){
      shrinkers[i].SetInput(shrinkers[i-1].GetOutput());
    } //this output is 10 x 15

    lrs[0].SetInput(blacksq.GetOutput());
    lrs[0].SetInput2(shrinkers[4].GetOutput());
    lrs[1].SetInput(shrinkers[4].GetOutput());
    lrs[1].SetInput2(blacksq.GetOutput());

    lrs[2].SetInput(lrs[0].GetOutput());
    lrs[2].SetInput2(blacksq.GetOutput());
    lrs[3].SetInput(lrs[2].GetOutput());
    lrs[3].SetInput2(lrs[1].GetOutput()); //OHOHO

    lrs[4].SetInput(lrs[0].GetOutput());
    lrs[4].SetInput2(shrinkers[4].GetOutput());
    lrs[5].SetInput(lrs[4].GetOutput());
    lrs[5].SetInput2(lrs[1].GetOutput()); //OHHHO

    tbs[0].SetInput(blackln.GetOutput());
    tbs[0].SetInput2(lrs[3].GetOutput());

    tbs[1].SetInput(lrs[5].GetOutput());
    tbs[1].SetInput2(lrs[3].GetOutput());

    tbs[2].SetInput(tbs[0].GetOutput());
    tbs[2].SetInput2(tbs[1].GetOutput());

    tbs[3].SetInput(tbs[2].GetOutput());
    tbs[3].SetInput2(blackln.GetOutput());

    //This Makes the H
    //Now on to the A
    Color halfblsq(10, 8, 0, 0, 0);
    Color halfnotbl(10, 7, 100, 100, 100);
    LRCombine lrsa[5];
    TBCombine tbsa[5];

    tbsa[0].SetInput(halfblsq.GetOutput());
    tbsa[0].SetInput2(halfnotbl.GetOutput());
    lrsa[0].SetInput(lrs[0].GetOutput());
    lrsa[0].SetInput2(tbsa[0].GetOutput());
    lrsa[1].SetInput(lrsa[0].GetOutput());
    lrsa[1].SetInput2(lrs[1].GetOutput());

    tbsa[1].SetInput(blackln.GetOutput());
    tbsa[1].SetInput2(lrs[5].GetOutput()); //OOOOO -- OHHHO

    tbsa[2].SetInput(lrsa[1].GetOutput());
    tbsa[2].SetInput2(lrs[3].GetOutput());

    tbsa[3].SetInput(tbsa[1].GetOutput());
    tbsa[3].SetInput2(tbsa[2].GetOutput());

    tbsa[4].SetInput(tbsa[3].GetOutput());
    tbsa[4].SetInput2(blackln.GetOutput());

    lrsa[3].SetInput(tbs[3].GetOutput());
    lrsa[3].SetInput2(tbsa[4].GetOutput());

    //now the N and the K 10 x 15 -- 5 , 7

    /*   TODO: fill in fun stuff here   */

    TBCombine tbsn[5];

    tbsn[0].SetInput(blackln.GetOutput());
    tbsn[0].SetInput2(lrs[5].GetOutput());

    tbsn[1].SetInput(lrs[3].GetOutput());
    tbsn[1].SetInput2(lrs[3].GetOutput());

    tbsn[2].SetInput(tbsn[0].GetOutput());
    tbsn[2].SetInput2(tbsn[1].GetOutput());

    tbsn[3].SetInput(tbsn[2].GetOutput());
    tbsn[3].SetInput2(blackln.GetOutput());

    //Now for the K
    LRCombine lrsk[5];

    lrsk[0].SetInput(blacksq.GetOutput());
    lrsk[0].SetInput2(shrinkers[4].GetOutput());

    lrsk[1].SetInput(lrsk[0].GetOutput());
    lrsk[1].SetInput2(shrinkers[4].GetOutput());

    lrsk[2].SetInput(blacksq.GetOutput());
    lrsk[2].SetInput2(blacksq.GetOutput());

    lrsk[3].SetInput(lrsk[1].GetOutput());
    lrsk[3].SetInput2(lrsk[2].GetOutput());

    TBCombine tbsk[5];

    tbsk[0].SetInput(blackln.GetOutput());
    tbsk[0].SetInput2(lrs[3].GetOutput());

    tbsk[1].SetInput(tbsk[0].GetOutput());
    tbsk[1].SetInput2(lrsk[3].GetOutput());

    tbsk[2].SetInput(lrs[3].GetOutput());
    tbsk[2].SetInput2(blackln.GetOutput());

    tbsk[3].SetInput(tbsk[1].GetOutput());
    tbsk[3].SetInput2(tbsk[2].GetOutput());
    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */

    LRCombine endc;
    endc.SetInput(tbsn[3].GetOutput());
    endc.SetInput2(tbsk[3].GetOutput());

    TBCombine endt;
    endt.SetInput(lrsa[3].GetOutput());
    endt.SetInput2(endc.GetOutput());

    Blur bl1;
    Blur bl2;

    bl1.SetInput(endt.GetOutput());
    bl2.SetInput(bl1.GetOutput());

    Image *finalImage = bl2.GetOutput();//bl.GetOutput();//shrinkers[4].GetOutput();

    /* ================================ */
    /*  END STUDENT MODIFIABLE SECTION  */
    /* ================================ */



    try
    {
        finalImage->Update();
    }
    catch (DataFlowException &)
    {
        ofstream ofile("my_exception");
        if (ofile.fail())
        {
             cerr << "Something is wrong ... can't open my_exception"
                  << " for opening" << endl;
             exit(EXIT_FAILURE);
        }
        ofile << "Exception found!" << endl;
        exit(EXIT_SUCCESS);
    }

    CheckSum cs;
    cs.SetInput(finalImage);
    cs.OutputCheckSum("my_checksum");

    //printf("%d, %d\n", finalImage->getHeight(), finalImage->getWidth());

    if (argc == 3)
    {
        PNMwriter writer;
        writer.SetInput(finalImage);
        writer.Write("3H.pnm");
    }
    Logger::Finalize();
}
