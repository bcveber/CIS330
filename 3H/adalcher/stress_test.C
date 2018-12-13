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
    //PNMreader reader("../images/puddles.pnm");  // note: filename must be "../images/image_name.pnm"


    /*   Remember that game where you take a paddle and bounce a ball to destroy bricks?   */
	Color brick(105, 79, 209, 204, 133);
	Color hMortar(105, 12, 159, 159, 159);
	Color vMortar(16, 79, 159, 159, 159);
	
	LRCombine hwall1;	// 1
	LRCombine hwall2;	// 2
	LRCombine hwall3;	// 4
	LRCombine hwall4;	// 8

	LRCombine hwall5;	// 8 + 4
	LRCombine hwall6;	// 12 + 2
	LRCombine hwall7;	// 14 + 1
	LRCombine hwall8;	// 15 + 1
	
	hwall1.SetInput(brick.GetOutput());
	hwall1.SetInput2(vMortar.GetOutput());
	hwall2.SetInput(hwall1.GetOutput());
	hwall2.SetInput2(hwall1.GetOutput());
	hwall3.SetInput(hwall2.GetOutput());
	hwall3.SetInput2(hwall2.GetOutput());
	hwall4.SetInput(hwall3.GetOutput());
	hwall4.SetInput2(hwall3.GetOutput());

	hwall5.SetInput(hwall4.GetOutput());
	hwall5.SetInput2(hwall3.GetOutput());
	hwall6.SetInput(hwall5.GetOutput());
	hwall6.SetInput2(hwall2.GetOutput());
	hwall7.SetInput(hwall6.GetOutput());
	hwall7.SetInput2(hwall1.GetOutput());
	hwall8.SetInput(hwall7.GetOutput());
	hwall8.SetInput2(brick.GetOutput());

	TBCombine vwall1;	// 1
	TBCombine vwall2;	// 2
	TBCombine vwall3;	// 4
	TBCombine vwall4;	// 8

	TBCombine vwall5;	// 8 + 2
	TBCombine vwall6;	// 10 + 1
	TBCombine vwall7;	// 11 + mortar

	vwall1.SetInput(brick.GetOutput());
	vwall1.SetInput2(hMortar.GetOutput());
	vwall2.SetInput(vwall1.GetOutput());
	vwall2.SetInput2(vwall1.GetOutput());
	vwall3.SetInput(vwall2.GetOutput());
	vwall3.SetInput2(vwall2.GetOutput());
	vwall4.SetInput(vwall3.GetOutput());
	vwall4.SetInput2(vwall3.GetOutput());

	vwall5.SetInput(vwall4.GetOutput());
	vwall5.SetInput2(vwall2.GetOutput());
	vwall6.SetInput(vwall5.GetOutput());
	vwall6.SetInput2(brick.GetOutput());
	vwall7.SetInput(hMortar.GetOutput());
	vwall7.SetInput2(vwall6.GetOutput());
	// END WALLS

	// START COLOURED BRICKS
	Color lime(110, 80, 108, 228, 30);
	Color lvb(5, 80, 98, 218, 20);
	Color lhb(120, 5, 98, 218, 20);
	LRCombine lb1;
	LRCombine lb2;
	TBCombine lb3;
	TBCombine limeBrick;
	lb1.SetInput(lvb.GetOutput());
	lb1.SetInput2(lime.GetOutput());
	lb2.SetInput(lb1.GetOutput());
	lb2.SetInput2(lvb.GetOutput());
	lb3.SetInput(lhb.GetOutput());
	lb3.SetInput2(lb2.GetOutput());
	limeBrick.SetInput(lb3.GetOutput());
	limeBrick.SetInput2(lhb.GetOutput());

	Color orange(110, 80, 255, 164, 26);
	Color ovb(5, 80, 245, 154, 16);
	Color ohb(120, 5, 245, 154, 16);
	LRCombine ob1;
	LRCombine ob2;
	TBCombine ob3;
	TBCombine orangeBrick;
	ob1.SetInput(ovb.GetOutput());
	ob1.SetInput2(orange.GetOutput());
	ob2.SetInput(ob1.GetOutput());
	ob2.SetInput2(ovb.GetOutput());
	ob3.SetInput(ohb.GetOutput());
	ob3.SetInput2(ob2.GetOutput());
	orangeBrick.SetInput(ob3.GetOutput());
	orangeBrick.SetInput2(ohb.GetOutput());
	
	Color cherry(110, 80, 249, 0, 68);
	Color cvb(5, 80, 239, 0, 58);
	Color chb(120, 5, 239, 0, 58);
	LRCombine cb1;
	LRCombine cb2;
	TBCombine cb3;
	TBCombine cherryBrick;
	cb1.SetInput(cvb.GetOutput());
	cb1.SetInput2(cherry.GetOutput());
	cb2.SetInput(cb1.GetOutput());
	cb2.SetInput2(cvb.GetOutput());
	cb3.SetInput(chb.GetOutput());
	cb3.SetInput2(cb2.GetOutput());
	cherryBrick.SetInput(cb3.GetOutput());
	cherryBrick.SetInput2(chb.GetOutput());
	
	Color cinnamon(110, 80, 159, 35, 26);
	Color svb(5, 80, 149, 25, 16);
	Color shb(120, 5, 149, 25, 16);
	LRCombine sb1;
	LRCombine sb2;
	TBCombine sb3;
	TBCombine cinnamonBrick;
	sb1.SetInput(svb.GetOutput());
	sb1.SetInput2(cinnamon.GetOutput());
	sb2.SetInput(sb1.GetOutput());
	sb2.SetInput2(svb.GetOutput());
	sb3.SetInput(shb.GetOutput());
	sb3.SetInput2(sb2.GetOutput());
	cinnamonBrick.SetInput(sb3.GetOutput());
	cinnamonBrick.SetInput2(shb.GetOutput());
	
	Color grape(110, 80, 134, 11, 193);
	Color rvb(5, 80, 124, 1, 183);
	Color rhb(120, 5, 124, 1, 183);
	LRCombine rb1;
	LRCombine rb2;
	TBCombine rb3;
	TBCombine grapeBrick;
	rb1.SetInput(rvb.GetOutput());
	rb1.SetInput2(grape.GetOutput());
	rb2.SetInput(rb1.GetOutput());
	rb2.SetInput2(rvb.GetOutput());
	rb3.SetInput(rhb.GetOutput());
	rb3.SetInput2(rb2.GetOutput());
	grapeBrick.SetInput(rb3.GetOutput());
	grapeBrick.SetInput2(rhb.GetOutput());
	
	Color tuttifrutti(110, 80, 251, 185, 216);
	Color tvb(5, 80, 241, 175, 206);
	Color thb(120, 5, 241, 175, 206);
	LRCombine tb1;
	LRCombine tb2;
	TBCombine tb3;
	TBCombine tuttifruttiBrick;
	tb1.SetInput(tvb.GetOutput());
	tb1.SetInput2(tuttifrutti.GetOutput());
	tb2.SetInput(tb1.GetOutput());
	tb2.SetInput2(tvb.GetOutput());
	tb3.SetInput(thb.GetOutput());
	tb3.SetInput2(tb2.GetOutput());
	tuttifruttiBrick.SetInput(tb3.GetOutput());
	tuttifruttiBrick.SetInput2(thb.GetOutput());
	
	Color blueberry(110, 80, 17, 104, 249);
	Color bvb(5, 80, 7, 94, 239);
	Color bhb(120, 5, 7, 94, 239);
	LRCombine bb1;
	LRCombine bb2;
	TBCombine bb3;
	TBCombine blueberryBrick;
	bb1.SetInput(bvb.GetOutput());
	bb1.SetInput2(blueberry.GetOutput());
	bb2.SetInput(bb1.GetOutput());
	bb2.SetInput2(bvb.GetOutput());
	bb3.SetInput(bhb.GetOutput());
	bb3.SetInput2(bb2.GetOutput());
	blueberryBrick.SetInput(bb3.GetOutput());
	blueberryBrick.SetInput2(bhb.GetOutput());

	unsigned char bgr = 114;
	unsigned char bgg = 228;
	unsigned char bgb = 223;
	Color background(120, 90, bgr, bgg, bgb);
	// END COLOURS

	// BEGIN FILL
	LRCombine bbLR;

	LRCombine tf1LR;
	LRCombine tf2LR;

	LRCombine gr1LR;
	LRCombine gr2LR;

	LRCombine ci1LR;
	LRCombine ci2LR;

	LRCombine ch1LR;
	LRCombine ch2LR;

	LRCombine or1LR;
	LRCombine or2LR;

	LRCombine li1LR;
	LRCombine li2LR;

	Blur blurRow1;
	Blur blurRow2;
	Blur blurRow3;

	bbLR.SetInput(blueberryBrick.GetOutput());
	bbLR.SetInput2(blueberryBrick.GetOutput());

	tf1LR.SetInput(tuttifruttiBrick.GetOutput());
	tf1LR.SetInput2(bbLR.GetOutput());
	tf2LR.SetInput2(tuttifruttiBrick.GetOutput());
	tf2LR.SetInput(tf1LR.GetOutput());

	gr1LR.SetInput(grapeBrick.GetOutput());
	gr1LR.SetInput2(tf2LR.GetOutput());
	gr2LR.SetInput2(grapeBrick.GetOutput());
	gr2LR.SetInput(gr1LR.GetOutput());

	ci1LR.SetInput(cinnamonBrick.GetOutput());
	ci1LR.SetInput2(gr2LR.GetOutput());
	ci2LR.SetInput2(cinnamonBrick.GetOutput());
	ci2LR.SetInput(ci1LR.GetOutput());

	ch1LR.SetInput(cherryBrick.GetOutput());
	ch1LR.SetInput2(ci2LR.GetOutput());
	ch2LR.SetInput2(cherryBrick.GetOutput());
	ch2LR.SetInput(ch1LR.GetOutput());

	or1LR.SetInput(orangeBrick.GetOutput());
	or1LR.SetInput2(ch2LR.GetOutput());
	or2LR.SetInput2(orangeBrick.GetOutput());
	or2LR.SetInput(or1LR.GetOutput());

	li1LR.SetInput(limeBrick.GetOutput());
	li1LR.SetInput2(or2LR.GetOutput());
	li2LR.SetInput2(limeBrick.GetOutput());
	li2LR.SetInput(li1LR.GetOutput());
	
	blurRow1.SetInput(li2LR.GetOutput());
	blurRow2.SetInput(blurRow1.GetOutput());
	blurRow3.SetInput(blurRow2.GetOutput());
	
	TBCombine row1;
	LRCombine row2;
	LRCombine row3;
	Color rowHFill(15, 180, bgr, bgg, bgb);	

	row1.SetInput(blurRow3.GetOutput());
	row1.SetInput2(blurRow3.GetOutput());
	row2.SetInput(rowHFill.GetOutput());
	row2.SetInput2(row1.GetOutput());
	row3.SetInput(row2.GetOutput());
	row3.SetInput2(rowHFill.GetOutput());

	// END FILL

	// BEGIN PADDLE
	
	Color pBase(300, 70, 187, 142, 123);
	Color pEnd(10, 70, 102, 68, 53);
	LRCombine p1;
	LRCombine p2;
	Blur paddle;
	p1.SetInput(pEnd.GetOutput());
	p1.SetInput2(pBase.GetOutput());
	p2.SetInput(p1.GetOutput());
	p2.SetInput2(pEnd.GetOutput());
	paddle.SetInput(p2.GetOutput());

	Color lbFill(800, 70, bgr, bgg, bgb);
	Color rbFill(590, 70, bgr, bgg, bgb);
	LRCombine p3;
	LRCombine paddleFilled;

	p3.SetInput(lbFill.GetOutput());
	p3.SetInput2(paddle.GetOutput());
	paddleFilled.SetInput(p3.GetOutput());
	paddleFilled.SetInput2(rbFill.GetOutput());
	// END PADDLE

	// BEGIN BALL
	Color ballC(80, 80, 247, 247, 0);
	Color ballV(5, 80, 200, 200, 0);
	Color ballH(90, 5, 200, 200, 0);
	LRCombine ball1;
	LRCombine ball2;
	TBCombine ball3;
	TBCombine ball4;

	ball1.SetInput(ballV.GetOutput());
	ball1.SetInput2(ballC.GetOutput());
	ball2.SetInput(ball1.GetOutput());
	ball2.SetInput2(ballV.GetOutput());
	ball3.SetInput(ballH.GetOutput());
	ball3.SetInput2(ball2.GetOutput());
	ball4.SetInput(ball3.GetOutput());
	ball4.SetInput2(ballH.GetOutput());

	Color backSquare(90, 90, bgr, bgg, bgb);
        #define its 5
	LRCombine rightFill[its];
	LRCombine leftFill[its];
	TBCombine combined[its];
	Shrinker shrink[its];
	Blur blur[its];

	rightFill[0].SetInput(ball4.GetOutput());
	rightFill[0].SetInput2(backSquare.GetOutput());
	leftFill[0].SetInput(backSquare.GetOutput());
	leftFill[0].SetInput2(backSquare.GetOutput());
	combined[0].SetInput(rightFill[0].GetOutput());
	combined[0].SetInput2(leftFill[0].GetOutput());
	shrink[0].SetInput(combined[0].GetOutput());
	blur[0].SetInput(shrink[0].GetOutput());

	for(int i = 1; i < its; ++i)
	{
		rightFill[i].SetInput(ball4.GetOutput());
		rightFill[i].SetInput2(backSquare.GetOutput());
		leftFill[i].SetInput(backSquare.GetOutput());
		leftFill[i].SetInput2(blur[i-1].GetOutput());
		combined[i].SetInput(rightFill[i].GetOutput());
		combined[i].SetInput2(leftFill[i].GetOutput());
		shrink[i].SetInput(combined[i].GetOutput());
		blur[i].SetInput(shrink[i].GetOutput());
	}

	Color ballLFill(800, 90, bgr, bgg, bgb);
	Color ballRFill(820, 90, bgr, bgg, bgb);
	LRCombine bFill1;
	LRCombine bFill2;
	
	bFill1.SetInput(ballLFill.GetOutput());
	bFill1.SetInput2(blur[its-1].GetOutput());
	bFill2.SetInput(bFill1.GetOutput());
	bFill2.SetInput2(ballRFill.GetOutput());
	//END BALL

	//BEGIN IMAGE COMPOSITION
	TBCombine ballPaddle;
	TBCombine BPFill1;
	TBCombine BPFill2;
	TBCombine RowFill;
	TBCombine inComplete;
	Color BPFillBack(1710, 450, bgr, bgg, bgb);
	Color BPFillBottom(1710, 79, bgr, bgg, bgb);
	Color RowFillBack(1710, 132, bgr, bgg, bgb);
	ballPaddle.SetInput(bFill2.GetOutput());
	ballPaddle.SetInput2(paddleFilled.GetOutput());
	BPFill1.SetInput(BPFillBack.GetOutput());
	BPFill1.SetInput2(ballPaddle.GetOutput());
	BPFill2.SetInput(BPFill1.GetOutput());
	BPFill2.SetInput2(BPFillBottom.GetOutput());
	RowFill.SetInput(RowFillBack.GetOutput());
	RowFill.SetInput2(row3.GetOutput());
	inComplete.SetInput(RowFill.GetOutput());
	inComplete.SetInput2(BPFill2.GetOutput());
	//END IMAGE COMPOSITION

	Image* inner = inComplete.GetOutput();
	LRCombine in1;
	LRCombine in2;
	TBCombine in3;

	in1.SetInput(vwall7.GetOutput());
	in1.SetInput2(inner);
	in2.SetInput(in1.GetOutput());
	in2.SetInput2(vwall7.GetOutput());
	
	in3.SetInput(hwall8.GetOutput());
	in3.SetInput2(in2.GetOutput());

    Image *finalImage = in3.GetOutput();

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
