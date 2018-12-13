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
    PNMreader reader("../images/question_marks.pnm");  // note: filename must be "../images/image_name.pnm"
    
    Blur bl;
    Blur bl2;
    Blur bl3;
    Blur bl4;
    Subtract sb;

    #define iterations 2

    TBCombine tb1[iterations];
    TBCombine tb2[iterations];
    TBCombine tb3[iterations];
    LRCombine lr1[iterations];
    LRCombine lr2[iterations];
    LRCombine lr3[iterations];
    LRCombine lr4[iterations];
    Shrinker sh[iterations];
    Shrinker sh2[iterations];

    bl.SetInput(reader.GetOutput());
    bl2.SetInput(bl.GetOutput());
    bl3.SetInput(bl2.GetOutput());
    bl4.SetInput(bl3.GetOutput());
    sb.SetInput(reader.GetOutput());
    sb.SetInput2(bl4.GetOutput());

    Image* input = reader.GetOutput();

    for(int i = 0; i < iterations; i++) {
        lr1[i].SetInput(input);
        lr1[i].SetInput2(input);

        Image* lr1o = lr1[i].GetOutput();
        lr2[i].SetInput(lr1o);
        lr2[i].SetInput2(lr1o);

        lr3[i].SetInput(input);
        lr3[i].SetInput2(sb.GetOutput());
        Image* lr3o = lr3[i].GetOutput();
        lr4[i].SetInput(lr3o);
        lr4[i].SetInput2(lr3o);
        
        Image* lr2o = lr2[i].GetOutput();
        Image* lr4o = lr4[i].GetOutput();
        tb1[i].SetInput(lr2o);
        tb1[i].SetInput2(lr4o);
        tb2[i].SetInput(lr4o);
        tb2[i].SetInput2(lr2o);
        Image* tb1o = tb1[i].GetOutput();
        Image* tb2o = tb2[i].GetOutput();
        tb3[i].SetInput(tb1o);
        tb3[i].SetInput2(tb2o);
        
        sh[i].SetInput(tb3[i].GetOutput());
        sh2[i].SetInput(sh[i].GetOutput());

        input = sh2[i].GetOutput();
    }
    
    Image *finalImage = sh2[iterations - 1].GetOutput();

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
