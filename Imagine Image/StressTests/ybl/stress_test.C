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
    
    Blur br;
    Mirror mr;
    Grayscale gs;
    LRCombine lr;
    Shrinker sr;
    TBCombine tb;
    Rotate rt;
    Rotate rt2;
    
    Blur br2;
    Mirror mr2;
    Grayscale gs2;
    LRCombine lr2;
    Shrinker sr2;
    TBCombine tb2;
    Rotate rt3;
    Rotate rt4;
    
    Blur br3;
    Mirror mr3;
    Grayscale gs3;
    LRCombine lr3;
    Shrinker sr3;
    TBCombine tb3;
    Rotate rt5;
    Rotate rt6;
    
    Grayscale gs4;
    
    
    mr.SetInput(reader.GetOutput());
    br.SetInput(mr.GetOutput());
    gs.SetInput(br.GetOutput());
    
    sr.SetInput(gs.GetOutput());
    
    lr.SetInput(sr.GetOutput());
    lr.SetInput2(sr.GetOutput());
    tb.SetInput(lr.GetOutput());
    tb.SetInput2(lr.GetOutput());
    rt.SetInput(tb.GetOutput());
    rt2.SetInput(rt.GetOutput());
    
    mr2.SetInput(rt2.GetOutput());
    br2.SetInput(mr2.GetOutput());
    gs2.SetInput(br2.GetOutput());
    
    sr2.SetInput(gs2.GetOutput());
    
    lr2.SetInput(sr2.GetOutput());
    lr2.SetInput2(sr2.GetOutput());
    tb2.SetInput(lr2.GetOutput());
    tb2.SetInput2(lr2.GetOutput());
    rt3.SetInput(tb2.GetOutput());
    rt4.SetInput(rt3.GetOutput());
    
    mr3.SetInput(rt4.GetOutput());
    br3.SetInput(mr3.GetOutput());
    gs3.SetInput(br3.GetOutput());
    
    sr3.SetInput(gs3.GetOutput());
    
    lr3.SetInput(sr3.GetOutput());
    lr3.SetInput2(sr3.GetOutput());
    tb3.SetInput(lr3.GetOutput());
    tb3.SetInput2(lr3.GetOutput());
    rt5.SetInput(tb3.GetOutput());
    rt6.SetInput(rt5.GetOutput());

    gs4.SetInput(rt6.GetOutput());
    
    
    //sb.GetOutput()->Update();
    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = gs4.GetOutput();
    
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
