#pragma once

#include "renderer/vu1_program.hpp"

class color_triangles_clip_verts: VU1Program
{
public:
	color_triangles_clip_verts();
	~color_triangles_clip_verts();

	virtual std::string getStringName() { return "color_triangles_clip_verts"; }
};