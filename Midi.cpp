#include <stdexcept>

#include "Midi.h"

void Midi::Thread::Parse(std::istream &f)
{
	unsigned char data[14];
	f.read((char *)data, 14);
	if(f.eof())
		throw std::runtime_error("Cannot read MThd record: file truncated");
	if(data[0] != 0x4D || data[1] != 0x54 || data[2] != 0x68 || data[3] != 0x64)
		throw std::runtime_error("Invalid MThd magic");
	if(data[4] != 0x00 || data[5] != 0x00 || data[6] != 0x00 || data[7] != 0x06)
		throw std::runtime_error("Invalid MThd struct length");
	short int format = data[8] << 8 | data[9];
	if(format < 0 || format > 2)
		throw std::runtime_error("Invalid format type");
	short int tracknum = data[10] << 8 | data[11];
	bpm = data[12] << 8 | data[13];
	tracks.resize(tracknum);
	for(int i = 0; i < tracknum; i++)
		tracks[i].Parse(f);
}

void Midi::Track::Parse(std::istream &f)
{
	unsigned char data[8];
	f.read((char *)data, 8);
	if(f.eof())
		throw std::runtime_error("Cannot read MTrk record: file truncated");
	if(data[0] != 0x4D || data[1] != 0x54 || data[2] != 0x72 || data[3] != 0x6B)
		throw std::runtime_error("Invalid MTrk magic");
	int stop = (data[4] << 24 | data[5] << 16 | data[6] << 8 | data[7]);
	stop += f.tellg();
	std::list<Midi::Event> events;
	int running = 0;
	while(f.tellg() < stop)
	{
		Midi::Event event;
		running = event.Parse(f, running);
		events.push_back(event);
	}
	unsigned long int time = 0;
	std::list<Midi::Note> starts;
	for(std::list<Midi::Event>::const_iterator i = events.begin(), end = events.end(); i != end; i++)
	{
		time += i->delta;
		if(i->type == Midi::Event::NoteOn)
		{
			Midi::Note note;
			note.note = i->param1;
			note.start = time;
			starts.push_back(note);
		}
		else if(i->type == Midi::Event::NoteOff)
			for(std::list<Midi::Note>::iterator j = starts.begin(), end = starts.end(); j != end; j++)
				if(j->note == i->param1)
				{
					j->duration = time - j->start;
					notes.push_back(*j);
					starts.erase(j);
					break;
				}
	}
	if(starts.begin() != starts.end())
		throw std::runtime_error("Unpaired note events within track");
}

long unsigned int read_vl(std::istream &f)
{
	unsigned char a = f.get();
	if(a & 0x80)
	{
		unsigned char b = f.get();
		if(b & 0x80)
		{
			unsigned char c = f.get();
			if(c & 0x80)
			{
				unsigned char d = f.get();
				return (a & 0x7F) << 21 | (b & 0x7F) << 14 | (c & 0x7F) << 7 | d;
			}
			else
				return (a & 0x7F) << 14 | (b & 0x7F) << 7 | c;
		}
		else
			return (a & 0x7F) << 7 | b;
	}
	else
		return a;
}

int Midi::Event::Parse(std::istream &f, int running)
{
	delta = read_vl(f);
	int p = f.get();
	type = p >> 4;
	if(!(type & 0x8))
	{
		type = running;
		f.unget();
	}
	if(type == Midi::Event::Extra)
	{
		f.ignore(1);
		int length = f.get();
		f.ignore(length);
	}
	else
	{
		param1 = f.get();
		param2 = f.get();
	}
	if(f.eof())
		throw std::runtime_error("Cannot read event: file truncated");
	return type;
}
