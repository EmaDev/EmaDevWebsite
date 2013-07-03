#include "Web.h"


namespace Web
{
	namespace Utility
	{
		string intToString(int _int)
		{
			stringstream ss;
			string s;
			ss << _int;
			s = ss.str();
			return s;
		}
		string doubleToString(double _double)
		{
			stringstream ss;
			string s;
			ss << _double;
			s = ss.str();
			return s;
		}
		int stringToInt(string _string)
		{
			int numb;
			istringstream(_string)>>numb;
			return numb;
		}
		double stringToDouble(string _string)
		{
			double numb;
			istringstream(_string)>>numb;
			return numb;
		}
		string stringClone(string orig)
		{
			string ns = string(orig.length( ), ' ');
			copy(orig.begin( ), orig.end( ), ns.begin());
			return ns;
		}
		string urlDecode(string &src)
		{
			string ret;
			char ch;
			unsigned int i, ii;
			for (i=0; i<src.length(); i++)
			{
				if (int(src[i])==37) {
					sscanf_s(src.substr(i+1,2).c_str(), "%x", &ii);
					ch=static_cast<char>(ii);
					ret+=ch;
					i=i+2;
				} else
				{
        			if (int(src[i])==43)
					{
            			src[i] = ' ';
					}
					ret+=src[i];
				}
			}
			return (ret);
		}
		void replaceAll(string& str, const string& from, const string& to)
		{
			if(from.empty())
				return;
			size_t start_pos = 0;
			while((start_pos = str.find(from, start_pos)) != string::npos)
			{
				str.replace(start_pos, from.length(), to);
				start_pos += to.length();
			}
		}
	}
}