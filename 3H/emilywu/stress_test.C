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

    /* you may want one or more readers! */  // note: filename must be "../images/image_name.pnm"
    PNMreader reader2("../images/hank.pnm");

    Shrinker s1;
    Shrinker s2;
    Shrinker s3;
    Shrinker uphank;
    Rotate r1;
    Rotate downhank;

    LRCombine hanks2;
    LRCombine hanks3;
    LRCombine hanks4;
    LRCombine hanks5;

    LRCombine empty2;
    LRCombine empty3;
    LRCombine empty4;
    LRCombine empty8;
    LRCombine empty16;
    LRCombine empty32;
    LRCombine empty48;
    LRCombine emptyrow;

    LRCombine n0fff0up1;
    LRCombine n0fff0up;

    LRCombine f000fdown1;
    LRCombine f000fdown;

    LRCombine f000fup1;
    LRCombine f000fup;

    LRCombine f0000up;
    LRCombine f0000down;

    LRCombine ffff0down1;
    LRCombine ffff0down;

    LRCombine n0f0f0up1;
    LRCombine n0f0f0up2;
    LRCombine n0f0f0up;

    LRCombine n0f0f0down1;
    LRCombine n0f0f0down2;
    LRCombine n0f0f0down;

    LRCombine n00f00up1;
    LRCombine n00f00up;

    TBCombine C1;
    TBCombine C2;
    TBCombine C3;
    TBCombine C4;
    TBCombine C5;
    TBCombine C;

    TBCombine O1;
    TBCombine O2;
    TBCombine O3;
    TBCombine O4;
    TBCombine O5;
    TBCombine O;

    TBCombine V1;
    TBCombine V2;
    TBCombine V3;
    TBCombine V4;
    TBCombine V;

    TBCombine F1;
    TBCombine F2;
    TBCombine F3;
    TBCombine F4;
    TBCombine F;

    TBCombine E1;
    TBCombine E2;
    TBCombine E3;
    TBCombine E4;
    TBCombine E5;
    TBCombine E;

    TBCombine space2;
    TBCombine space3;
    TBCombine space4;
    TBCombine space;

    LRCombine margin2;
    LRCombine margin3;
    LRCombine margin4;

    LRCombine Cspace;
    LRCombine Ospace;
    LRCombine Vspace;
    LRCombine Espace;
    LRCombine Fspace;

    LRCombine FE;
    LRCombine marginC;
    LRCombine OV;
    LRCombine marginCOV;
    LRCombine FEFE;
    LRCombine marginCOVFEFE;
    LRCombine marginCRVOFEFEmargin;

    TBCombine tbmargin;

    TBCombine image1;
    TBCombine image2;
    TBCombine image3;
    TBCombine image4;
    TBCombine image;

    Color background(81, 121, 255, 255, 255);

    s1.SetInput(reader2.GetOutput());
    uphank.SetInput(s1.GetOutput());

    r1.SetInput(uphank.GetOutput());
    downhank.SetInput(r1.GetOutput());

    
    //empty row setup
    empty2.SetInput(background.GetOutput());
    empty2.SetInput2(background.GetOutput());

    empty3.SetInput(background.GetOutput());
    empty3.SetInput2(empty2.GetOutput());

    empty4.SetInput(empty2.GetOutput());
    empty4.SetInput2(empty2.GetOutput());

    empty8.SetInput(empty4.GetOutput());
    empty8.SetInput2(empty4.GetOutput());

    empty16.SetInput(empty8.GetOutput());
    empty16.SetInput2(empty8.GetOutput());

    empty32.SetInput(empty16.GetOutput());
    empty32.SetInput2(empty16.GetOutput());

    empty48.SetInput(empty16.GetOutput());
    empty48.SetInput2(empty32.GetOutput());

    emptyrow.SetInput(background.GetOutput());
    emptyrow.SetInput2(empty48.GetOutput());

    //hanks setup
    hanks2.SetInput(uphank.GetOutput());
    hanks2.SetInput2(downhank.GetOutput());

    hanks3.SetInput(hanks2.GetOutput());
    hanks3.SetInput2(uphank.GetOutput());

    hanks4.SetInput(hanks2.GetOutput());
    hanks4.SetInput2(hanks2.GetOutput());

    hanks5.SetInput(hanks3.GetOutput());
    hanks5.SetInput2(hanks2.GetOutput());

    //fills setup
    n0fff0up1.SetInput(background.GetOutput());
    n0fff0up1.SetInput2(hanks3.GetOutput());
    n0fff0up.SetInput(n0fff0up1.GetOutput());
    n0fff0up.SetInput2(background.GetOutput());

    f000fdown1.SetInput(downhank.GetOutput());
    f000fdown1.SetInput2(empty3.GetOutput());
    f000fdown.SetInput(f000fdown1.GetOutput());
    f000fdown.SetInput2(downhank.GetOutput());

    f000fup1.SetInput(uphank.GetOutput());
    f000fup1.SetInput2(empty3.GetOutput());
    f000fup.SetInput(f000fup1.GetOutput());
    f000fup.SetInput2(uphank.GetOutput());

    f0000up.SetInput(uphank.GetOutput());
    f0000up.SetInput2(empty4.GetOutput());

    f0000down.SetInput(downhank.GetOutput());
    f0000down.SetInput2(empty4.GetOutput());

    ffff0down1.SetInput(downhank.GetOutput());
    ffff0down1.SetInput2(hanks3.GetOutput());
    ffff0down.SetInput(ffff0down1.GetOutput());
    ffff0down.SetInput2(background.GetOutput());

    n0f0f0up1.SetInput(background.GetOutput());
    n0f0f0up1.SetInput2(uphank.GetOutput());
    n0f0f0up2.SetInput(n0f0f0up1.GetOutput());
    n0f0f0up2.SetInput2(n0f0f0up1.GetOutput());
    n0f0f0up.SetInput(n0f0f0up2.GetOutput());
    n0f0f0up.SetInput2(background.GetOutput());

    n0f0f0down1.SetInput(background.GetOutput());
    n0f0f0down1.SetInput2(downhank.GetOutput());
    n0f0f0down2.SetInput(n0f0f0down1.GetOutput());
    n0f0f0down2.SetInput2(n0f0f0down1.GetOutput());
    n0f0f0down.SetInput(n0f0f0down2.GetOutput());
    n0f0f0down.SetInput2(background.GetOutput());

    n00f00up1.SetInput(empty2.GetOutput());
    n00f00up1.SetInput2(uphank.GetOutput());
    n00f00up.SetInput(n00f00up1.GetOutput());
    n00f00up.SetInput2(empty2.GetOutput());

    C1.SetInput(n0fff0up.GetOutput());
    C1.SetInput2(f0000down.GetOutput());
    C2.SetInput(C1.GetOutput());
    C2.SetInput2(f0000up.GetOutput());
    C3.SetInput(C2.GetOutput());
    C3.SetInput2(f0000down.GetOutput());
    C4.SetInput(C3.GetOutput());
    C4.SetInput2(f0000up.GetOutput());
    C5.SetInput(C4.GetOutput());
    C5.SetInput2(f000fdown.GetOutput());
    C.SetInput(C5.GetOutput());
    C.SetInput2(n0fff0up.GetOutput());

    O1.SetInput(n0fff0up.GetOutput());
    O1.SetInput2(f000fdown.GetOutput());
    O2.SetInput(O1.GetOutput());
    O2.SetInput2(f000fup.GetOutput());
    O3.SetInput(O2.GetOutput());
    O3.SetInput2(f000fdown.GetOutput());
    O4.SetInput(O3.GetOutput());
    O4.SetInput2(f000fup.GetOutput());
    O5.SetInput(O4.GetOutput());
    O5.SetInput2(f000fdown.GetOutput());
    O.SetInput(O5.GetOutput());
    O.SetInput2(n0fff0up.GetOutput());

    V1.SetInput(f000fup.GetOutput());
    V1.SetInput2(f000fdown.GetOutput());
    V2.SetInput(V1.GetOutput());
    V2.SetInput2(V1.GetOutput());
    V3.SetInput(n0f0f0up.GetOutput());
    V3.SetInput2(n0f0f0down.GetOutput());
    V4.SetInput(V2.GetOutput());
    V4.SetInput2(V3.GetOutput());
    V.SetInput(V4.GetOutput());
    V.SetInput2(n00f00up.GetOutput());

    F1.SetInput(f0000down.GetOutput());
    F1.SetInput2(f0000up.GetOutput());
    F2.SetInput(ffff0down.GetOutput());
    F2.SetInput2(f0000up.GetOutput());
    F3.SetInput(hanks5.GetOutput());
    F3.SetInput2(F1.GetOutput());
    F4.SetInput(F2.GetOutput());
    F4.SetInput2(F1.GetOutput());
    F.SetInput(F3.GetOutput());
    F.SetInput2(F4.GetOutput());

    E1.SetInput(hanks5.GetOutput());
    E1.SetInput2(f0000down.GetOutput());
    E2.SetInput(E1.GetOutput());
    E2.SetInput2(f0000up.GetOutput());
    E3.SetInput(E2.GetOutput());
    E3.SetInput2(ffff0down.GetOutput());
    E4.SetInput(E3.GetOutput());
    E4.SetInput2(f0000up.GetOutput());
    E5.SetInput(E4.GetOutput());
    E5.SetInput2(f0000down.GetOutput());
    E.SetInput(E5.GetOutput());
    E.SetInput2(hanks5.GetOutput());

    space2.SetInput(background.GetOutput());
    space2.SetInput2(background.GetOutput());
    space3.SetInput(space2.GetOutput());
    space3.SetInput2(background.GetOutput());
    space4.SetInput(space2.GetOutput());
    space4.SetInput2(space2.GetOutput());
    space.SetInput(space3.GetOutput());
    space.SetInput2(space4.GetOutput());

    margin2.SetInput(space.GetOutput());
    margin2.SetInput2(space.GetOutput());
    margin3.SetInput(margin2.GetOutput());
    margin3.SetInput2(space.GetOutput());
    margin4.SetInput(margin2.GetOutput());
    margin4.SetInput2(margin2.GetOutput());

    Cspace.SetInput(C.GetOutput());
    Cspace.SetInput2(space.GetOutput());
    Ospace.SetInput(O.GetOutput());
    Ospace.SetInput2(space.GetOutput());
    Vspace.SetInput(V.GetOutput());
    Vspace.SetInput2(space.GetOutput());
    Fspace.SetInput(F.GetOutput());
    Fspace.SetInput2(space.GetOutput());
    Espace.SetInput(E.GetOutput());
    Espace.SetInput2(space.GetOutput());

    FE.SetInput(Fspace.GetOutput());
    FE.SetInput2(Espace.GetOutput());
    marginC.SetInput(margin4.GetOutput());
    marginC.SetInput2(Cspace.GetOutput());
    OV.SetInput(Ospace.GetOutput());
    OV.SetInput2(Vspace.GetOutput());
    marginCOV.SetInput(marginC.GetOutput());
    marginCOV.SetInput2(OV.GetOutput());
    FEFE.SetInput(FE.GetOutput());
    FEFE.SetInput2(FE.GetOutput());
    marginCOVFEFE.SetInput(marginCOV.GetOutput());
    marginCOVFEFE.SetInput2(FEFE.GetOutput());

    marginCRVOFEFEmargin.SetInput(marginCOVFEFE.GetOutput());
    marginCRVOFEFEmargin.SetInput2(margin3.GetOutput());

    tbmargin.SetInput(emptyrow.GetOutput());
    tbmargin.SetInput2(emptyrow.GetOutput());

    image1.SetInput(tbmargin.GetOutput());
    image1.SetInput2(marginCRVOFEFEmargin.GetOutput());

    /*image2.SetInput(emptyrow.GetOutput());
    image2.SetInput2(marginCRVOFEFEmargin.GetOutput());

    image3.SetInput(image2.GetOutput());
    image3.SetInput2(image2.GetOutput());

    image4.SetInput(image1.GetOutput());
    image4.SetInput2(image3.GetOutput());*/

    image.SetInput(image1.GetOutput());
    image.SetInput2(tbmargin.GetOutput());

    /*   TODO: fill in fun stuff here   */


    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    //Image *finalImage = marginCRVOFEFEmargin.GetOutput();
    Image *finalImage = image.GetOutput();

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
