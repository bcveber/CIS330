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


    PNMreader readerHank("../images/hank.pnm");
    Shrinker sr;
    Shrinker sr2;
    Shrinker sr3;
    Blur br;
    Blur br2;
    Blender bl;
    Blender bl2;
    Mirror mr;
    Mirror mr2;
    Mirror mr3;
    Rotate rt;
    Rotate rt2;
    Subtract st;
    Subtract st2;
    Grayscale gr;
    TBCombine tb;
    TBCombine tb1;
    TBCombine tb2;
    TBCombine tb3;
    TBCombine tb4;
    TBCombine tb5;
    TBCombine tb6;
    TBCombine tb7;
    TBCombine tb8;
    TBCombine tb9;
    TBCombine tb10;
    TBCombine tb11;
    TBCombine tb12;
    LRCombine lr;
    LRCombine lr2;
    LRCombine lr3;
    LRCombine lr4;
    LRCombine lr5;
    Color gold(326, 484, 255, 215, 0);
    Color random(326, 484, 121, 22, 150);
    tb.SetInput(readerHank.GetOutput());
    tb.SetInput2(readerHank.GetOutput());
    tb1.SetInput(tb.GetOutput());
    tb1.SetInput2(tb.GetOutput());
    tb5.SetInput(tb1.GetOutput());
    tb5.SetInput2(tb1.GetOutput());
    
    tb6.SetInput(random.GetOutput());
    tb6.SetInput2(random.GetOutput());
    tb7.SetInput(tb.GetOutput());
    tb7.SetInput2(tb6.GetOutput());
    tb8.SetInput(tb7.GetOutput());
    tb8.SetInput2(tb6.GetOutput());
    tb9.SetInput(tb8.GetOutput());
    tb9.SetInput2(tb.GetOutput());
    
    tb10.SetInput(tb.GetOutput());
    tb10.SetInput2(readerHank.GetOutput());
    tb11.SetInput(tb10.GetOutput());
    tb11.SetInput2(tb6.GetOutput());
    tb12.SetInput(tb11.GetOutput());
    tb12.SetInput2(tb10.GetOutput());


    lr.SetInput(tb12.GetOutput());
    lr.SetInput2(tb5.GetOutput());
    lr3.SetInput(tb9.GetOutput());
    lr3.SetInput2(lr.GetOutput());
    lr4.SetInput(tb9.GetOutput());
    lr4.SetInput2(lr3.GetOutput());

    mr.SetInput(lr4.GetOutput());
    lr2.SetInput(mr.GetOutput());
    lr2.SetInput2(lr4.GetOutput());  

    sr.SetInput(lr2.GetOutput());
    sr2.SetInput(sr.GetOutput());
    sr3.SetInput(sr2.GetOutput());

    st.SetInput(gold.GetOutput());
    st.SetInput2(sr3.GetOutput());
    gr.SetInput(readerHank.GetOutput());
    br.SetInput(gr.GetOutput());
    br2.SetInput(br.GetOutput());
    bl.SetInput(br2.GetOutput());
    bl.SetInput2(st.GetOutput());
    rt.SetInput(bl.GetOutput());
    rt2.SetInput(rt.GetOutput());
    bl2.SetInput(rt2.GetOutput());
    bl2.SetInput2(bl.GetOutput());
    st2.SetInput(rt2.GetOutput());
    st2.SetInput2(bl.GetOutput());

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = bl2.GetOutput();

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
