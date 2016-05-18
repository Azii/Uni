import org.junit.* ;
import static org.junit.Assert.* ;

public class PictureUnitTest {
    private double delta = 1e-5;

    @Test(timeout=1000)
    public void testRepairPicture(){
        RGBColor[][] imageMatrix = new RGBColor[100][100];
        for (int w=0; w<100; w++){
            for (int h=0; h<100; h++){
                if ((w==50) & (h==50)){
                    imageMatrix[w][h] = new RGBColor(255,255,255);
                } else {
                    imageMatrix[w][h] = new RGBColor(0,0,0);
                }
            }
        }
        Picture p = new Picture(imageMatrix);
        p.repairPicture();
        assertTrue("The white pixel was not repaired", !(p.getImageMatrix()[50][50].isWhite()));
    }

    @Test(timeout=1000)
    public void testRot90DegRight(){
        RGBColor[][] imageMatrix = new RGBColor[100][100];
        for (int w=0; w<100; w++){
            for (int h=0; h<100; h++){
                if ((w==20) & (h==20)){
                    imageMatrix[w][h] = new RGBColor(255,255,255);
                } else {
                    imageMatrix[w][h] = new RGBColor(0,0,0);
                }
            }
        }
        Picture p = new Picture(imageMatrix);
        p.rot90DegRight();
        assertTrue("The white pixel was not rotated", !(p.getImageMatrix()[20][20].isWhite()));
        assertTrue("The white pixel was not rotated", (p.getImageMatrix()[79][20].isWhite()));

    }


    @Test(timeout=1000)
    public void testRot180DegRight(){
        RGBColor[][] imageMatrix = new RGBColor[100][100];
        for (int w=0; w<100; w++){
            for (int h=0; h<100; h++){
                if ((w==20) & (h==20)){
                    imageMatrix[w][h] = new RGBColor(255,255,255);
                } else {
                    imageMatrix[w][h] = new RGBColor(0,0,0);
                }
            }
        }
        Picture p = new Picture(imageMatrix);
        p.rot180Deg();
        assertTrue("The white pixel was not rotated", !(p.getImageMatrix()[20][20].isWhite()));
        assertTrue("The white pixel was not rotated", (p.getImageMatrix()[79][79].isWhite()));

    }

}

