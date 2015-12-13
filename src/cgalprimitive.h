/*
 *   RapCAD - Rapid prototyping CAD IDE (www.rapcad.org)
 *   Copyright (C) 2010-2014 Giles Bathgate
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
#if USE_CGAL
#ifndef CGALPRIMITIVE_H
#define CGALPRIMITIVE_H

#include "cgal.h"

#include <QVector>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Nef_polyhedron_3.h>
#include <CGAL/Nef_nary_union_3.h>
#include "cgalpolygon.h"
#include "cgalvolume.h"
#include "primitive.h"

#include "contrib/Boolean_operations.h"

namespace CGAL
{
typedef Polyhedron_3<Kernel3> Polyhedron3;
typedef Nef_polyhedron_3<Kernel3> NefPolyhedron3;
}

typedef CGAL::Polyhedron_3<CGAL::Kernel3,Enriched_items> MEPP_Polyhedron;

class CGALPrimitive : public Primitive
{
public:
	CGALPrimitive();
	~CGALPrimitive();
	CGALPrimitive(CGAL::Polyhedron3 poly);
	void setType(Primitive_t);
	Polygon* createPolygon();
	void createVertex(Point);
	void appendVertex(CGAL::Point3);
	void prependVertex(CGAL::Point3);
	bool overlaps(Primitive*);
	Primitive* group(Primitive*);
	Primitive* join(Primitive*);
	void add(Primitive*,bool);
	Primitive* combine();
	Primitive* intersection(Primitive*);
	Primitive* difference(Primitive*);
	Primitive* symmetric_difference(Primitive*);
	Primitive* minkowski(Primitive*);
	Primitive* inset(const decimal);
	Primitive* decompose();
	Primitive* complement();
	Primitive* copy();
	Primitive* triangulate();
	CGAL::Cuboid3 getBounds();
	void transform(TransformMatrix*);
	/* Don't call this method instead use getCGALPolygons */
	Q_DECL_DEPRECATED QList<Polygon*> getPolygons() const;
	QList<CGALPolygon*> getCGALPolygons() const;
	/* Don't call this method instead use getCGALPoints */
	Q_DECL_DEPRECATED QList<Point> getPoints() const;
	QList<CGAL::Point3> getCGALPoints() const;
	const CGAL::NefPolyhedron3& getNefPolyhedron();
	CGAL::Polyhedron3* getPolyhedron();
	bool isEmpty();
	bool isFullyDimentional();
	QList<Primitive*> getChildren();
	void appendChild(Primitive*);
	void discrete(int);
	CGAL::Circle3 getRadius();
	CGALVolume getVolume(bool);
	MEPP_Polyhedron* polyhedron;
private:
	void init();
	void buildPrimitive();
	CGAL::NefPolyhedron3* createPolyline(QVector<CGAL::Point3> pl);

	QList<Primitive*> children;
	QList<CGAL::Point3> points;
	QList<CGALPolygon*> polygons;
	CGAL::NefPolyhedron3* nefPolyhedron;
	Primitive_t type;

	/* Simple wrapper class to enable Primitive
	 * to be used with CGAL::Nef_nary_union_3 */
	class Unionable
	{
	public:
		Unionable() {}
		Unionable(Primitive* p, bool f) { primitive=p; force=f; }
		Unionable& operator+(Unionable&);
		Primitive* primitive;
		bool force;
	};

	CGAL::Nef_nary_union_3<Unionable>* nUnion;
	static CGAL::NefPolyhedron3* singlePoint;
};

#endif // CGALPRIMITIVE_H
#endif
