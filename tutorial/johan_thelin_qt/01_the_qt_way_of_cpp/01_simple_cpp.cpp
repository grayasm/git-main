#include <string>

using std::string;

class MyClass
{
public:
	MyClass(const string& text)
		: m_text(text) { }
	const string& text() const { return m_text; }
	void SetText(const string& text)
	{ m_text = text; }
	int getLengthOfText() const { return m_text.size(); }

private:
	string m_text;
};
