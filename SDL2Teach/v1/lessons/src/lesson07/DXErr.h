#include<fstream>
#include<string>
#include <time.h>

#ifndef __DXERR_H__
#define __DXERR_H__
#define DXFunc __func__
#define DXLine __LINE__
#define DXFile __FILE__
namespace DXkite
{
	/* enum Oper { Endl, Time, Date, File }; */
	class DXErr
	{
	  private:
		std::ofstream file;
		time_t Etime;
		struct tm *Err;
		int close();
		int Start();
	  public:
		  DXErr() = default;
		  template < typename T > int put(T ty);
		  std::string Time();

	};
	  template < typename T > DXErr & operator<<(DXErr & in, T Out)
	{
		in.put(Out);
		return in;
	}
	std::string DXErr::Time()
	{
		char str[20];
		sprintf(str, "%02d:%02d:%02d ", Err->tm_hour, Err->tm_min,
				Err->tm_sec);
		return str;
	}
	int DXErr::Start()
	{

		time(&Etime);
		Err = localtime(&Etime);
		char filename[20];
		sprintf(filename, "%04d-%02d-%02d.log", 1900 + Err->tm_year,
				Err->tm_mon + 1, Err->tm_mday);
		file.open(filename, std::ios::app);
	}

	template < typename T > int DXErr::put(T type)
	{
		Start();
		file << type;
		close();
	}

	int DXErr::close()
	{
		file.close();
	}
	DXErr & operator<<(DXErr & in, std::string Fun())
	{
		// endl
		if (Fun() == "Endl")
			in << "\n";
		// time
		if (Fun() == "Time")
			in << __TIME__;
		if (Fun() == "TimeNow")
			in << in.Time();
		if (Fun() == "Date")
			in << __DATE__;
		return in;
	}

	std::string Endl()
	{
		return "Endl";
	}
	std::string Time()
	{
		return "Time";
	}
	std::string TimeNow()
	{
		return "TimeNow";
	}
	std::string Date()
	{
		return "Date";
	}
}

#endif							/* */