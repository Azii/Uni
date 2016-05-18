/**
 * Represents a Cube
 * @author AlgoDat
 */
public class Cube extends Cuboid {

	double length;
	/*
	 * Constructor without parameter
	 */
	public Cube() {
		super();
	}
	/*
	 * Constructor with one parameter
	 * 
	 * @param length the side length of the cube
	 */
	public Cube(double length) {
		super(length, length, length);
	}

	public double getLength(){
		return super.length;
	}
	//TODO: ggf. weitere Methoden und member implementieren
	@Override
	double calculateVolume() {
		return Math.pow(super.length, 3);
	}
	@Override
	double calculateSurface() {
		return super.calculateSurface();
	}
}

