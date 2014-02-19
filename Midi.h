#include <istream>
#include <list>
#include <vector>

namespace Midi
{
	class Event
	{
	public:
		enum
		{
			NoteOff = 0x8,
			NoteOn = 0x9,
			NoteChange = 0xA,
			Controller = 0xB,
			Program = 0xC,
			Channel = 0xD,
			Bend = 0xE,
			Extra = 0xF
		};
		unsigned long int delta;
		int type;
		int param1, param2;
		int Parse(std::istream &f, int running);
	};

	typedef struct
	{
		unsigned long int start, duration;
		int note;
	}
	Note;

	class Track
	{
	public:
		std::list<Note> notes;
		void Parse(std::istream &f);
	};

	class Thread
	{
	public:
		std::vector<Track> tracks;
		long int bpm;
		void Parse(std::istream &f);
	};
};
