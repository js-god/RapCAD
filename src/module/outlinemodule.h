/*
 *   RapCAD - Rapid prototyping CAD IDE (www.rapcad.org)
 *   Copyright (C) 2010-2017 Giles Bathgate
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OUTLINEMODULE_H
#define OUTLINEMODULE_H

#include "module.h"
#include "onceonly.h"

class OutlineModule : public Module
{
	Q_DECLARE_TR_FUNCTIONS(OutlineModule)
public:
	OutlineModule(Reporter*, bool);
	Node* evaluate(Context*) override;
private:
	static OnceOnly depricateWarning;
	bool legacy;
};

#endif // OUTLINEMODULE_H
