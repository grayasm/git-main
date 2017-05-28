/*
  See CMakeLists.txt for building this source.
 */

#include <iostream>
#include <string>

using std::string;

class MyClass
{
public:
	MyClass(const string& text)
	{
		m_text = text;
	}

	const string& text() const
	{
		return m_text;
	}

	void setText(const string& text)
	{
		m_text = text;
	}

	int getLengthOfText() const
	{
		return m_text.size();
	}

private:
	string m_text;
};

int main(int, char**)
{
	MyClass *a, *b, *c;

	a = new MyClass("foo");
	b = new MyClass("ba-a-ar");
	c = new MyClass("baz");

	std::cout << a->text() << " (" << a->getLengthOfText() << ")" << std::endl;
	a->setText(b->text());
	std::cout << a->text() << " (" << a->getLengthOfText() << ")" << std::endl;

	int result = a->getLengthOfText() - c->getLengthOfText();

	delete a;
	delete b;
	delete c;

	return result;
}
