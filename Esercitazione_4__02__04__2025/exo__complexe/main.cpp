#include <iostream>
#include <type_traits>

// Template class for complex numbers
// This class models complex numbers with real and imaginary parts
// The template parameter T should be a floating point type (float or double)
template <typename T> requires std::floating_point<T>
class Complex {
private:
    T real;  // Real part of the complex number
    T imag;  // Imaginary part of the complex number

public:
    // Default constructor: initializes both real and imaginary parts to 0
    Complex() : real(0), imag(0) {}
    
    // Constructor that initializes only the real part, imaginary part set to 0
    explicit Complex(T r) : real(r), imag(0) {}
    
    // Constructor that initializes both real and imaginary parts
    Complex(T r, T i) : real(r), imag(i) {}

    // Function to display the complex number in a readable format
    void display() const {
        std::cout << real;
        if (imag >= 0) std::cout << " + " << imag << "i";
        else std::cout << " - " << -imag << "i";
        std::cout << std::endl;
    }

    // Returns the real part of the complex number
    T real_part() const { return real; }
    
    // Returns the imaginary part of the complex number
    T imaginary() const { return imag; }

    // Returns the complex conjugate (same real part, opposite imaginary part)
    Complex conjugate() const { return Complex(real, -imag); }

    // Operator += for addition
    // Adds another complex number to this one and updates the current object
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }

    // Operator + for addition
    // Returns a new complex number representing the sum of this and another complex number
    Complex operator+(const Complex& other) const {
        Complex comp = *this;
        comp += other;
        return comp;
    }

    // Operator *= for multiplication
    // Multiplies this complex number by another and updates the current object
    Complex& operator*=(const Complex& other) {
        T a = real, b = imag;
        T c = other.real, d = other.imag;
        real = a * c - b * d;  // Formula: (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
        imag = a * d + b * c;
        return *this;
    }

    // Operator * for multiplication
    // Returns a new complex number representing the product of this and another complex number
    Complex operator*(const Complex& other) const {
        Complex comp = *this;
        comp *= other;
        return comp;
    }

    // Stream operator for output
    // Allows printing a complex number using std::cout
    friend std::ostream& operator<<(std::ostream& os, const Complex& comp) {
        os << comp.real_part();
        if (comp.imaginary() >= 0) os << " + " << comp.imaginary() << "i";
        else os << " - " << -comp.imaginary() << "i";
        return os;
    }
};

int main() {
    // Create two complex numbers
    Complex<double> c1(3.5, 2.0);
    Complex<double> c2(1.5, 1.0);
    
    // Compute their sum and product
    Complex<double> sum = c1 + c2;
    Complex<double> prod = c1 * c2;
    Complex<double> ccc=c1.conjugate();
    
    // Display results
    std::cout << "c1: " << c1 << std::endl;
    std::cout << "c2: " << c2 << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Product: " << prod << std::endl;
    std::cout << "conjugate of c1" << ccc << std::endl;
    return 0;
}
