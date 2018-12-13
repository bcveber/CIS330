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

    Color whiteOneByOne(10, 10, 255, 192, 203);
    Color blackOneByOne(10, 10, 255, 105, 180);
    Color blackOneByThree(10, 30, 255, 105, 180);
    Color blackFourByOne(40, 10, 255, 105, 180);
    Color whiteFourByThree(40, 30, 255, 192, 203);
    Color whiteSpace(10, 50, 255, 192, 203);
    Color blackOneByFive(10, 50, 255, 105, 180);
    Color whiteOneByTwo(10, 20, 255, 192, 203);
    Color whiteTwentyFiveByOne(250, 10, 255, 192, 203);
    Color whiteOneByThree(10, 30, 255, 192, 203);
    Color whiteOneByFour(10, 40, 255, 192, 203);
    Color whiteThirtyEightByOneThirty(38, 130, 255, 192, 203); 

   // Letter C
    TBCombine tbC;
    tbC.SetInput(whiteOneByOne.GetOutput());
    tbC.SetInput2(blackOneByThree.GetOutput());
    TBCombine tbC2;
    tbC2.SetInput(tbC.GetOutput());
    tbC2.SetInput2(whiteOneByOne.GetOutput());
    TBCombine tbC3;
    tbC3.SetInput(blackFourByOne.GetOutput());
    tbC3.SetInput2(whiteFourByThree.GetOutput());
    TBCombine tbC4;
    tbC4.SetInput(tbC3.GetOutput());
    tbC4.SetInput2(blackFourByOne.GetOutput());
    LRCombine lrC;
    lrC.SetInput(tbC2.GetOutput());
    lrC.SetInput2(tbC4.GetOutput());
    LRCombine lrC2;
    lrC2.SetInput(lrC.GetOutput());
    lrC2.SetInput2(whiteSpace.GetOutput());   
    LRCombine letterC;
    letterC.SetInput(whiteSpace.GetOutput());
    letterC.SetInput2(lrC2.GetOutput());

    // Letter R
    TBCombine tbR;
    tbR.SetInput(blackOneByOne.GetOutput());
    tbR.SetInput2(whiteOneByOne.GetOutput());
    TBCombine tbR2;
    tbR2.SetInput(blackOneByOne.GetOutput());
    tbR2.SetInput2(whiteOneByTwo.GetOutput());
    TBCombine tbR3;
    tbR3.SetInput(tbR.GetOutput());
    tbR3.SetInput2(tbR2.GetOutput());
    LRCombine lrR;
    lrR.SetInput(blackOneByFive.GetOutput());
    lrR.SetInput2(tbR3.GetOutput());
    LRCombine lrR2;
    lrR2.SetInput(lrR.GetOutput());
    lrR2.SetInput2(tbR3.GetOutput());
    LRCombine lrR3;
    lrR3.SetInput(lrR2.GetOutput());
    lrR3.SetInput2(tbR3.GetOutput());
    TBCombine tbR4;
    tbR4.SetInput(whiteOneByOne.GetOutput());
    tbR4.SetInput2(blackOneByOne.GetOutput());
    TBCombine tbR5;
    tbR5.SetInput(tbR4.GetOutput());
    tbR5.SetInput2(tbR4.GetOutput());
    TBCombine tbR6;
    tbR6.SetInput(tbR5.GetOutput());
    tbR6.SetInput2(blackOneByOne.GetOutput());
    LRCombine lrR4;
    lrR4.SetInput(lrR3.GetOutput());
    lrR4.SetInput2(tbR6.GetOutput());
    LRCombine letterR;
    letterR.SetInput(lrR4.GetOutput());
    letterR.SetInput2(whiteSpace.GetOutput());

    // Letter A
    TBCombine trA;
    trA.SetInput(whiteOneByTwo.GetOutput()); 
    trA.SetInput2(blackOneByThree.GetOutput());
    TBCombine trA2;
    trA2.SetInput(whiteOneByOne.GetOutput());
    trA2.SetInput2(blackOneByOne.GetOutput());
    TBCombine trA3;
    trA3.SetInput(trA2.GetOutput());
    trA3.SetInput2(trA2.GetOutput());
    TBCombine trA4;
    trA4.SetInput(trA3.GetOutput());
    trA4.SetInput2(whiteOneByOne.GetOutput());
    TBCombine trA5;
    trA5.SetInput(blackOneByOne.GetOutput());
    trA5.SetInput2(whiteOneByTwo.GetOutput());
    TBCombine trA6;
    trA6.SetInput(trA5.GetOutput());
    trA6.SetInput2(blackOneByOne.GetOutput());
    TBCombine trA7;
    trA7.SetInput(trA6.GetOutput());
    trA7.SetInput2(whiteOneByOne.GetOutput());
    LRCombine lrA;
    lrA.SetInput(trA.GetOutput());
    lrA.SetInput2(trA4.GetOutput());
    LRCombine lrA2;
    lrA2.SetInput(lrA.GetOutput());
    lrA2.SetInput2(trA7.GetOutput());
    LRCombine lrA3;
    lrA3.SetInput(lrA2.GetOutput());
    lrA3.SetInput2(trA4.GetOutput());
    LRCombine lrA4;
    lrA4.SetInput(lrA3.GetOutput());
    lrA4.SetInput2(trA.GetOutput());
    LRCombine letterA;
    letterA.SetInput(lrA4.GetOutput());
    letterA.SetInput2(whiteSpace.GetOutput());

    // Letter Y
    TBCombine tbY;
    tbY.SetInput(blackOneByOne.GetOutput());
    tbY.SetInput2(whiteOneByFour.GetOutput());
    TBCombine tbY2;
    tbY2.SetInput(whiteOneByOne.GetOutput());    
    tbY2.SetInput2(blackOneByOne.GetOutput());
    TBCombine tbY3;
    tbY3.SetInput(tbY2.GetOutput());
    tbY3.SetInput2(whiteOneByThree.GetOutput());
    TBCombine tbY4;
    tbY4.SetInput(whiteOneByTwo.GetOutput());
    tbY4.SetInput2(blackOneByThree.GetOutput());
    LRCombine lrY;
    lrY.SetInput(tbY.GetOutput());
    lrY.SetInput2(tbY3.GetOutput());
    LRCombine lrY2;
    lrY2.SetInput(lrY.GetOutput());
    lrY2.SetInput2(tbY4.GetOutput());
    LRCombine lrY3;
    lrY3.SetInput(lrY2.GetOutput());
    lrY3.SetInput2(tbY3.GetOutput());
    LRCombine lrY4;
    lrY4.SetInput(lrY3.GetOutput());
    lrY4.SetInput2(tbY.GetOutput());
    LRCombine letterY;
    letterY.SetInput(lrY4.GetOutput());
    letterY.SetInput2(whiteSpace.GetOutput());

    // Combine letters
    LRCombine lettersCR;
    lettersCR.SetInput(letterC.GetOutput());
    lettersCR.SetInput2(letterR.GetOutput());
    LRCombine lettersCRA;
    lettersCRA.SetInput(lettersCR.GetOutput());
    lettersCRA.SetInput2(letterA.GetOutput());
    LRCombine lettersCRAY;
    lettersCRAY.SetInput(lettersCRA.GetOutput());
    lettersCRAY.SetInput2(letterY.GetOutput());

    // Combine Cray Cray
    Mirror mr;
    mr.SetInput(lettersCRAY.GetOutput());
    TBCombine cray;
    cray.SetInput(lettersCRAY.GetOutput());
    cray.SetInput2(whiteTwentyFiveByOne.GetOutput());
    TBCombine cray2;
    cray2.SetInput(whiteTwentyFiveByOne.GetOutput());
    cray2.SetInput2(cray.GetOutput());
    TBCombine crayCray;
    crayCray.SetInput(cray2.GetOutput());
    crayCray.SetInput2(mr.GetOutput());
    TBCombine crayCray2;
    crayCray2.SetInput(crayCray.GetOutput());
    crayCray2.SetInput2(whiteTwentyFiveByOne.GetOutput());
    LRCombine crayCray3;
    crayCray3.SetInput(whiteThirtyEightByOneThirty.GetOutput());
    crayCray3.SetInput2(crayCray2.GetOutput());
    LRCombine crayCray4;
    crayCray4.SetInput(crayCray3.GetOutput());
    crayCray4.SetInput2(whiteThirtyEightByOneThirty.GetOutput()); 
    TBCombine hankCrayCray;
    hankCrayCray.SetInput(reader.GetOutput());
    hankCrayCray.SetInput2(crayCray4.GetOutput());

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = hankCrayCray.GetOutput();

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

    if (argc == 3)
    {
        PNMwriter writer;
        writer.SetInput(finalImage);
        writer.Write("3H.pnm");
    }
    Logger::Finalize();
}
