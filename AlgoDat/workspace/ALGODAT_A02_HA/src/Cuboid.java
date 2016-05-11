/**
 * Represents a Cuboid
 * http://en.wikipedia.org/wiki/Cuboid
 * 
 * @author AlgoDat
 *
 */
public class Cuboid extends Body {

	double height, length, width;
	
	/*
	 * Constructor for a Cuboid object
	 */
	public Cuboid() {
		this(0, 0, 0);
	}
	/*
	 * Constructor for a Cuboid object
	 * 
	 * @param h height
	 * @param l length
	 * @param w width
	 */
	public Cuboid(double h, double l, double w) {
		this.height = h;
		this.length = l;
		this.width = w;
	}

	public double getHeight(){
		return this.height;
	}
	public double getLength(){
		return this.length;
	}
	public double getWidth(){
		return this.width;
	}
	//TODO: ggf. weitere Methoden und member implementieren

	@Override
	double calculateVolume()
	{
		return this.width * this.height * this.length;
	}
	
	@Override
	double calculateSurface()
	{
		double surface = 0;
		surface += 2 * width * height;
		surface += 2 * height * length;
		surface += 2 * length * width;
		return surface;
	}

}

