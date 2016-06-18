
public class Pair<T> {
	
	T first;
	T second;
	
	Pair(T first, T second) {
		this.first = first;
		this.second = second;
	}

	public T getFirst() {
		return this.first;
	}

	public T getSecond() {
		return this.second;
	}

	public void setFirst(T dt) {
		this.first = dt;
	}

	public void setSecond(T dt) {
		this.second = dt;
	}

	public void swap() {
		T temp = this.first;
		this.first = this.second;
		this.second = temp;
	}

	@Override
	public String toString() {
		String ret;
		try{
			ret = first.toString() + ", " + second.toString();
		}catch(Exception e)
		{
			ret =  "<not implemented>, <not implemented>";
		}
		return ret;
	}
}

