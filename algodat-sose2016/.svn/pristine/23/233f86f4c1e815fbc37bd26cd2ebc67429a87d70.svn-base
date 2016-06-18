class Sphere {
	
	Point center;
	double radius;
	
	Sphere(int x, int y, int z, double r){
		this(new Point(x, y, z), r);
	}
	
	Sphere(Point c, double r){
		center = c;
		radius = r;
	}
	
	double getX(){
		return this.center.getX();
	}

	double getY(){
		return this.center.getY();
	}

	double getZ(){
		return this.center.getZ();
	}


	double getRadius(){
		return this.radius;
	}

	double calculateDiameter(){
		return 2 * radius;
	}	
	
	double calculatePerimeter(){
		return 2 * radius * Math.PI;
	}
	
	double calculateVolume(){
		return 4 * Math.PI * Math.pow(radius, 3) / 3;
	}

}

