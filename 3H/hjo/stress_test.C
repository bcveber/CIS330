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

    unsigned char green[3] = {10, 64, 40};
    unsigned char gold[3] = {255, 215, 0};

    // In-Between & Edge Pieces
    Color between(94,384,green[0],green[1],green[2]); //between each letter and before&after first&last
    Color edge(1786,192,green[0],green[1],green[2]); //slab for top, middle, and bottom
    Color GOfiller(1128,384,green[0],green[1],green[2]); //filler after GO, includes "between" after O and padded 3x94 after S

    // G Pieces
    Color Ggreen_1(47,256,green[0],green[1],green[2]); //straight up side
    Color Ggreen_2(47,32,green[0],green[1],green[2]); //under G hang
    Color Ggreen_3(94,192,green[0],green[1],green[2]); //filler
    Color Ggold_1(47,256,gold[0],gold[1],gold[2]); //straight up side
    Color Ggold_2(188,64,gold[0],gold[1],gold[2]); //BOTH top and bottom
    Color Ggold_3(94,32,gold[0],gold[1],gold[2]); //G hang top
    Color Ggold_4(47,32,gold[0],gold[1],gold[2]); //G hang support
    // G put together
    LRCombine GleftMiddle;
    LRCombine GunderGhang;
    TBCombine Ghang;
    TBCombine GrightMiddle;
    LRCombine Gmiddle;
    TBCombine GtopWmid;
    TBCombine G;

    GleftMiddle.SetInput(Ggold_1.GetOutput());
    GleftMiddle.SetInput2(Ggreen_1.GetOutput());
    GunderGhang.SetInput(Ggreen_2.GetOutput());
    GunderGhang.SetInput2(Ggold_4.GetOutput());
    Ghang.SetInput(Ggold_3.GetOutput());
    Ghang.SetInput2(GunderGhang.GetOutput());
    GrightMiddle.SetInput(Ggreen_3.GetOutput());
    GrightMiddle.SetInput2(Ghang.GetOutput());
    Gmiddle.SetInput(GleftMiddle.GetOutput());
    Gmiddle.SetInput2(GrightMiddle.GetOutput());
    GtopWmid.SetInput(Ggold_2.GetOutput());
    GtopWmid.SetInput2(Gmiddle.GetOutput());
    G.SetInput(GtopWmid.GetOutput());
    G.SetInput2(Ggold_2.GetOutput());
    // G End

    // O Pieces
    Color Ogreen_1(94,256,green[0],green[1],green[2]); //filler
    Color Ogold_1(47,384,gold[0],gold[1],gold[2]); //sides
    Color Ogold_2(94,64,gold[0],gold[1],gold[2]); //top&bottom

    // O put together
    TBCombine OtopWFiller;
    TBCombine Omiddle;
    LRCombine OleftWmiddle;
    LRCombine O;

    OtopWFiller.SetInput(Ogold_2.GetOutput());
    OtopWFiller.SetInput2(Ogreen_1.GetOutput());
    Omiddle.SetInput(OtopWFiller.GetOutput());
    Omiddle.SetInput2(Ogold_2.GetOutput());
    OleftWmiddle.SetInput(Ogold_1.GetOutput());
    OleftWmiddle.SetInput2(Omiddle.GetOutput());
    O.SetInput(OleftWmiddle.GetOutput());
    O.SetInput2(Ogold_1.GetOutput());
    // O End

    // D Pieces
    Color Dgreen_1(47,32,green[0],green[1],green[2]); //corner fillers
         //reuse Ogreen_1 for D filler
    Color Dgold_1(47,256,gold[0],gold[1],gold[2]); //sides
    Color Dgold_2(141,64,gold[0],gold[1],gold[2]); //top*bottom w/o corners
    Color Dgold_3(47,32,gold[0],gold[1],gold[2]); //corner w/o filler

    // D put together
    TBCombine Dtopcorner;
    TBCombine Dbotcorner;
    LRCombine Dtop;
    LRCombine Dbot;
    LRCombine Dmid1; //with only left side
    LRCombine Dmid2; //full middle portion
    TBCombine DtopWmid;
    TBCombine D;

    Dtopcorner.SetInput(Dgreen_1.GetOutput());
    Dtopcorner.SetInput2(Dgold_3.GetOutput());
    Dbotcorner.SetInput(Dgold_3.GetOutput());
    Dbotcorner.SetInput2(Dgreen_1.GetOutput());
    Dtop.SetInput(Dgold_2.GetOutput());
    Dtop.SetInput2(Dtopcorner.GetOutput());
    Dbot.SetInput(Dgold_2.GetOutput());
    Dbot.SetInput2(Dbotcorner.GetOutput());
    Dmid1.SetInput(Dgold_1.GetOutput());
    Dmid1.SetInput2(Ogreen_1.GetOutput());
    Dmid2.SetInput(Dmid1.GetOutput());
    Dmid2.SetInput2(Dgold_1.GetOutput());
    DtopWmid.SetInput(Dtop.GetOutput());
    DtopWmid.SetInput2(Dmid2.GetOutput());
    D.SetInput(DtopWmid.GetOutput());
    D.SetInput2(Dbot.GetOutput());
    // D end

    // U Pieces
    Color Ugreen_1(94,320,green[0],green[1],green[2]); //filler
    Color Ugold_1(47,384,gold[0],gold[1],gold[2]); //sides
        //reuse Ogold_2 for U bottom

    // U put together
    TBCombine Umid;
    LRCombine Uleftmid;
    LRCombine U;

    Umid.SetInput(Ugreen_1.GetOutput());
    Umid.SetInput2(Ogold_2.GetOutput());
    Uleftmid.SetInput(Ugold_1.GetOutput());
    Uleftmid.SetInput2(Umid.GetOutput());
    U.SetInput(Uleftmid.GetOutput());
    U.SetInput2(Ugold_1.GetOutput());
    // U end

    // C Pieces
    Color Cgreen_1(141,256,green[0],green[1],green[2]); //filler
    Color Cgold_1(141,64,gold[0],gold[1],gold[2]); //top and bottom
        //reuse Ugold_1 for C left side

    // C put together
    TBCombine CtopWmid;
    TBCombine Crightside;
    LRCombine C;

    CtopWmid.SetInput(Cgold_1.GetOutput());
    CtopWmid.SetInput2(Cgreen_1.GetOutput());
    Crightside.SetInput(CtopWmid.GetOutput());
    Crightside.SetInput2(Cgold_1.GetOutput());
    C.SetInput(Ugold_1.GetOutput());
    C.SetInput2(Crightside.GetOutput());
    // C end

    // K Pieces
    Color Kgreen_1(47,166,green[0],green[1],green[2]); //big filler
    Color Kgreen_2(47,52,green[0],green[1],green[2]); //split filler
    Color Kgreen_3(47,83,green[0],green[1],green[2]); //fill-block
    Color Kgold_1(47,83,gold[0],gold[1],gold[2]); //k-block
    Color Kgold_2(47,52,gold[0],gold[1],gold[2]); //mid
        //reuse Ogold_1 for left side

    // K put together
    TBCombine Ku1; //upper outer blocks
    TBCombine Ku2; //upper inner blocks
    LRCombine Kuf1; //big fill+Ku2
    LRCombine Kuf2; //Kuf1+Ku1
    LRCombine Kmidfill; //2 spliter fillers
    LRCombine Kmid; // Kgold_2+Kmidfill
    TBCombine Kupperside; //Kuf2+Kmid
        //reuse Ku2 lower outer blocks
        //reuse Ku1 for lower inner blocks
    LRCombine Kdf1; //big fill+Ku1
    LRCombine Kdf2; //Kdf1+Ku2
    TBCombine Krightside; //Kupperside+Kdf2
    LRCombine K; //Ogold_1+Krightside

    Ku1.SetInput(Kgold_1.GetOutput());
    Ku1.SetInput2(Kgreen_3.GetOutput());
    Ku2.SetInput(Kgreen_3.GetOutput());
    Ku2.SetInput2(Kgold_1.GetOutput());
    Kuf1.SetInput(Kgreen_1.GetOutput());
    Kuf1.SetInput2(Ku2.GetOutput());
    Kuf2.SetInput(Kuf1.GetOutput());
    Kuf2.SetInput2(Ku1.GetOutput());
    Kmidfill.SetInput(Kgreen_2.GetOutput());
    Kmidfill.SetInput2(Kgreen_2.GetOutput());
    Kmid.SetInput(Kgold_2.GetOutput());
    Kmid.SetInput2(Kmidfill.GetOutput());
    Kupperside.SetInput(Kuf2.GetOutput());
    Kupperside.SetInput2(Kmid.GetOutput());
    Kdf1.SetInput(Kgreen_1.GetOutput());
    Kdf1.SetInput2(Ku1.GetOutput());
    Kdf2.SetInput(Kdf1.GetOutput());
    Kdf2.SetInput2(Ku2.GetOutput());
    Krightside.SetInput(Kupperside.GetOutput());
    Krightside.SetInput2(Kdf2.GetOutput());
    K.SetInput(Ogold_1.GetOutput());
    K.SetInput2(Krightside.GetOutput());
    // K end

    // S Pieces
    Color Sgreen_1(141,102,green[0],green[1],green[2]); //filler
    Color Sgold_1(188,52,gold[0],gold[1],gold[2]); //middle
    Color Sgold_2(47,102,gold[0],gold[1],gold[2]); //pillars
        //reuse Ggold_2 for top and bottom

    // S put together
    LRCombine Smid1;
    LRCombine Smid2;
    TBCombine Stop1; //top+mid1
    TBCombine Stop2; //Stop1+Sgold_1
    TBCombine Stop3; //Stop2+mid2
    TBCombine S;

    Smid1.SetInput(Sgold_2.GetOutput());
    Smid1.SetInput2(Sgreen_1.GetOutput());
    Smid2.SetInput(Sgreen_1.GetOutput());
    Smid2.SetInput2(Sgold_2.GetOutput());
    Stop1.SetInput(Ggold_2.GetOutput());
    Stop1.SetInput2(Smid1.GetOutput());
    Stop2.SetInput(Stop1.GetOutput());
    Stop2.SetInput2(Sgold_1.GetOutput());
    Stop3.SetInput(Stop2.GetOutput());
    Stop3.SetInput2(Smid2.GetOutput());
    S.SetInput(Stop3.GetOutput());
    S.SetInput2(Ggold_2.GetOutput());

    // S end

    // Final put together
    LRCombine leftMargin;
    LRCombine rightMargin;
    LRCombine go1;
    LRCombine go2;
    LRCombine go3;
    LRCombine GO;
    LRCombine ducks1;
    LRCombine ducks2;
    LRCombine ducks3;
    LRCombine ducks4;
    LRCombine ducks5;
    LRCombine ducks6;
    LRCombine ducks7;
    LRCombine ducks8;
    LRCombine ducks9;
    LRCombine DUCKS;
    TBCombine t1;
    TBCombine t2;
    TBCombine t3;
    TBCombine GODUCKS;

    leftMargin.SetInput(between.GetOutput());
    leftMargin.SetInput2(between.GetOutput());
    rightMargin.SetInput(leftMargin.GetOutput());
    rightMargin.SetInput2(between.GetOutput());
    go1.SetInput(leftMargin.GetOutput());
    go1.SetInput2(G.GetOutput());
    go2.SetInput(go1.GetOutput());
    go2.SetInput2(between.GetOutput());
    go3.SetInput(go2.GetOutput());
    go3.SetInput2(O.GetOutput());
    GO.SetInput(go3.GetOutput());
    GO.SetInput2(GOfiller.GetOutput());
    ducks1.SetInput(leftMargin.GetOutput());
    ducks1.SetInput2(D.GetOutput());
    ducks2.SetInput(ducks1.GetOutput());
    ducks2.SetInput2(between.GetOutput());
    ducks3.SetInput(ducks2.GetOutput());
    ducks3.SetInput2(U.GetOutput());
    ducks4.SetInput(ducks3.GetOutput());
    ducks4.SetInput2(between.GetOutput());
    ducks5.SetInput(ducks4.GetOutput());
    ducks5.SetInput2(C.GetOutput());
    ducks6.SetInput(ducks5.GetOutput());
    ducks6.SetInput2(between.GetOutput());
    ducks7.SetInput(ducks6.GetOutput());
    ducks7.SetInput2(K.GetOutput());
    ducks8.SetInput(ducks7.GetOutput());
    ducks8.SetInput2(between.GetOutput());
    ducks9.SetInput(ducks8.GetOutput());
    ducks9.SetInput2(S.GetOutput());
    DUCKS.SetInput(ducks9.GetOutput());
    DUCKS.SetInput2(rightMargin.GetOutput());
    t1.SetInput(edge.GetOutput());
    t1.SetInput2(GO.GetOutput());
    t2.SetInput(t1.GetOutput());
    t2.SetInput2(edge.GetOutput());
    t3.SetInput(t2.GetOutput());
    t3.SetInput2(DUCKS.GetOutput());
    GODUCKS.SetInput(t3.GetOutput());
    GODUCKS.SetInput2(edge.GetOutput());

    Grayscale gs;
    gs.SetInput(GODUCKS.GetOutput());

    LRCombine up;
    up.SetInput(GODUCKS.GetOutput());
    up.SetInput2(gs.GetOutput());

    LRCombine bot;
    bot.SetInput(gs.GetOutput());
    bot.SetInput2(GODUCKS.GetOutput());

    TBCombine final;
    final.SetInput(up.GetOutput());
    final.SetInput2(bot.GetOutput());

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = final.GetOutput();

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
