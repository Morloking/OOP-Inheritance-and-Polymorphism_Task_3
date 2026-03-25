#include <iostream>
#include <string>

class Figure {
public:
	Figure() {};
	std::string getName() const { return nameF; }
	int getSides() const { return amountSides; }
	virtual void printInfo() const {
		std::cout << getName() << ":\n"
			<< (check() ? "Правильная\n" : "Неправильная\n")
			<< "Количество сторон: " << getSides() << "\n";
		if (nameF == "Фигура") { std::cout << "\n"; } // -_- костыль для соответствия примеру
	}
	virtual std::string getLengths() const { return ""; }
	virtual std::string getCorners() const { return ""; }
	virtual bool check() const { return true; }

	virtual ~Figure() {};
protected:
	Figure(int sides, std::string name) :
		amountSides(sides), nameF(name) {}
private:
	int amountSides{ 0 };
	std::string nameF{ "Фигура" };
};

class Triangle :
	public Figure {
public:
	Triangle(int l1, int l2, int l3, int c1, int c2, int c3) :       //публичный конструктор для создания объектов обычного треугольника (вызывает протектед конструктор, но с именем треуг)
		Triangle(l1, l2, l3, c1, c2, c3, "Треугольник") {
	}
	void printInfo() const override {
		Figure::printInfo();
		std::cout << "Стороны: " << getLengths() << "\n"
			<< "Углы: " << getCorners() << "\n\n";
	}
	bool check() const override {
		if ((cor1 + cor2 + cor3) == 180) return true;
		else return false;
	}
protected:
	Triangle(int l1, int l2, int l3, int c1, int c2, int c3, const std::string name) :
		Figure(3, name) {
		len1 = l1; len2 = l2; len3 = l3;
		cor1 = c1; cor2 = c2; cor3 = c3;
	};

	std::string getLengths() const override { return "a = " + std::to_string(len1) + " b = " + std::to_string(len2) + " c = " + std::to_string(len3); }
	std::string getCorners() const override { return "A = " + std::to_string(cor1) + " B = " + std::to_string(cor2) + " C = " + std::to_string(cor3); }
protected:
	int len1{ 0 }, len2{ 0 }, len3{ 0 };
	int cor1{ 0 }, cor2{ 0 }, cor3{ 0 };
};

class Quadrangle :
	public Figure {
public:
	Quadrangle(int l1, int l2, int l3, int l4, int c1, int c2, int c3, int c4) :
		Quadrangle(l1, l2, l3, l4, c1, c2, c3, c4, "Четырёхугольник") {
	}
	void printInfo() const override {
		Figure::printInfo();
		std::cout << "Стороны: " << getLengths() << "\n"
			<< "Углы: " << getCorners() << "\n\n";
	}
	bool check() const override {
		if ((cor1 + cor2 + cor3 + cor4) == 360) return true;
		else return false;
	}
protected:
	Quadrangle(int l1, int l2, int l3, int l4, int c1, int c2, int c3, int c4, const std::string name) :
		Figure(4, name) {
		len1 = l1; len2 = l2; len3 = l3; len4 = l4;
		cor1 = c1; cor2 = c2; cor3 = c3; cor4 = c4;
	}

	std::string getLengths() const override { return "a = " + std::to_string(len1) + " b = " + std::to_string(len2) + " c = " + std::to_string(len3) + " d = " + std::to_string(len4); }
	std::string getCorners() const override { return "A = " + std::to_string(cor1) + " B = " + std::to_string(cor2) + " C = " + std::to_string(cor3) + " D = " + std::to_string(cor4); }
protected:
	int len1{ 0 }, len2{ 0 }, len3{ 0 }, len4{ 0 };
	int cor1{ 0 }, cor2{ 0 }, cor3{ 0 }, cor4{ 0 };
};


class RectangularTriangle :
	public Triangle {
public:
	RectangularTriangle(int l1, int l2, int l3, int c1, int c2) :
		Triangle(l1, l2, l3, c1, c2, 90, "Прямоугольный треугольник") {
	}
	bool check() const override {
		if (!Triangle::check()) return false;
		if (cor3 == 90) return true;
		else return false;
	}
};
class IsoscelesTriangle :
	public Triangle {
public:
	IsoscelesTriangle(int l1, int l2, int c1, int c2) :
		Triangle(l1, l2, l1, c1, c2, c1, "Равнобедренный треугольник") {
	}
	bool check() const override {
		if (!Triangle::check()) return false;
		if (len1 == len3 && cor1 == cor3) return true;
		else return false;
	}
};
class EquilateralTriangle :
	public Triangle {
public:
	EquilateralTriangle(int l1) :
		Triangle(l1, l1, l1, 60, 60, 60, "Равносторонний треугольник") {
	}
	bool check() const override {
		if (!Triangle::check()) return false;
		if (len1 == len2 && len2 == len3 && cor1 == cor2 && cor2 == cor3) return true;
		else return false;
	}
};

class Rectangle :
	public Quadrangle {
public:
	Rectangle(int l1, int l2) :
		Quadrangle(l1, l2, l1, l2, 90, 90, 90, 90, "Прямоугольник") {
	}
	bool check() const override {
		if (!Quadrangle::check()) return false;
		if (len1 == len3 && len2 == len4 && cor1 == 90 && cor2 == 90 && cor3 == 90 && cor4 == 90) return true;
		else return false;
	}
};
class Square :
	public Quadrangle {
public:
	Square(int l1) :
		Quadrangle(l1, l1, l1, l1, 90, 90, 90, 90, "Квадрат") {
	}
	bool check() const override {
		if (!Quadrangle::check()) return false;
		if (len1 == len2 && len2 == len3 && len3 == len4 && cor1 == 90 && cor2 == 90 && cor3 == 90 && cor4 == 90) return true;
		else return false;
	}
};
class Parallelogram :
	public Quadrangle {
public:
	Parallelogram(int l1, int l2, int c1, int c2) :
		Quadrangle(l1, l2, l1, l2, c1, c2, c1, c2, "Параллелограмм") {
	}
	bool check() const override {
		if (!Quadrangle::check()) return false;
		if (len1 == len3 && len2 == len4 && cor1 == cor3 && cor2 == cor4) return true;
		else return false;
	}
};
class Rhomb :
	public Quadrangle {
public:
	Rhomb(int l1, int c1, int c2) :
		Quadrangle(l1, l1, l1, l1, c1, c2, c1, c2, "Ромб") {
	}
	bool check() const override {
		if (!Quadrangle::check()) return false;
		if (len1 == len2 && len2 == len3 && len3 == len4 && cor1 == cor3 && cor2 == cor4) return true;
		else return false;
	}
};

int main() {
	setlocale(LC_ALL, "RUSSIAN");

	Figure figure;
	Triangle triangle(10, 20, 30, 50, 60, 70);
	RectangularTriangle wrongRectTriangle(10, 20, 30, 50, 60);
	RectangularTriangle correctRectTriangle(10, 20, 30, 50, 40);
	IsoscelesTriangle isosTriangle(10, 20, 50, 60);             
	EquilateralTriangle eqTriangle(30);

	Quadrangle quad(10, 20, 30, 40, 50, 60, 70, 80);
	Rectangle rectangle(10, 20);
	Square square(20);
	Parallelogram parallelogram(20, 30, 30, 40);
	Rhomb rhomb(30, 30, 40);

	figure.printInfo();
	triangle.printInfo();
	wrongRectTriangle.printInfo();
	correctRectTriangle.printInfo();
	isosTriangle.printInfo();
	eqTriangle.printInfo();

	quad.printInfo();
	rectangle.printInfo();
	square.printInfo();
	parallelogram.printInfo();
	rhomb.printInfo();

	return EXIT_SUCCESS;
}
