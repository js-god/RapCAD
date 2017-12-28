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

#include "polylinemodule.h"
#include "node/polylinenode.h"
#include "vectorvalue.h"
#include "numbervalue.h"

PolylineModule::PolylineModule(Reporter* r) : Module(r,"polyline")
{
	addDescription(tr("Constructs a line connecting multiple points."));
	addParameter("points",tr("The vertices are provided by the points list."));
	addParameter("lines",tr("The lines are a list of indices to the vertices"));
}

Node* PolylineModule::evaluate(Context* ctx) const
{
	auto* pointsVec=dynamic_cast<VectorValue*>(getParameterArgument(ctx,0));
	auto* linesVec=dynamic_cast<VectorValue*>(getParameterArgument(ctx,1));

	auto* pn=new PolylineNode(reporter);
	Primitive* p=pn->createPrimitive();

	if(!pointsVec)
		return pn;

	QList<Value*> points=pointsVec->getChildren();

	for(Value* point: points) {
		auto* pointVec=dynamic_cast<VectorValue*>(point);
		if(pointVec) {
			Point pt = pointVec->getPoint();
			p->createVertex(pt);

		}
	}

	/* If we are just given a single argument of points
	 * build a polyline from that. */
	if(!linesVec) {
		Polygon* pg=p->createPolygon();
		for(auto i=0; i<points.length(); ++i)
			pg->append(i);
		return pn;
	}

	/* Otherwise use the lines argument to describe the multiple
	 * polylines */
	QList<Value*> lines=linesVec->getChildren();

	for(Value* line: lines) {
		auto* lineVec=dynamic_cast<VectorValue*>(line);
		if(lineVec) {
			Polygon* pg=p->createPolygon();
			for(Value* indexVal: lineVec->getChildren()) {
				auto* indexNum=dynamic_cast<NumberValue*>(indexVal);
				if(indexNum) {
					int index = indexNum->toInteger();
					if(index>=0&&index<points.count()) {
						pg->append(index);
					}
				}
			}
		}
	}

	return pn;
}
