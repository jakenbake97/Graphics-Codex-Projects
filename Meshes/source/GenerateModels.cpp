#include <G3D-base/Array.h>
#include <G3D-base/G3DString.h>
#include <G3D-base/TextOutput.h>
#include <G3D-base/Vector3.h>

class GenerateModels
{
private:
	struct Face
	{
		G3D::Array<int> indices;
	};
	G3D::Array<Face> faces;
	G3D::Array<G3D::Vector3> vertices;
	
public:
	
	void MakeCylinder(float radius, float height, int numSegments, G3D::String fileName)
	{
		faces.clear();

		// cylinder parameters
		const float radianArc = G3D::toRadians( 360.0f / static_cast<float>(numSegments));
		const float ringOffset(height / 2.0f);

		

		G3D::Array<G3D::Vector3> topVertices; // temporary array of vertices to reduce the size of the loop
		for (int i = 0; i < numSegments; ++i)
		{
			G3D::Vector3 vert(radius * cos(radianArc * i), -ringOffset, radius * sin(radianArc * i));
			vertices.append(vert);

			vert.y = ringOffset;
			topVertices.append(vert);
		}
		vertices.append(topVertices);
		topVertices.clear();


		// Create the top and bottom endcap
		Face bottomEndCap;
		Face topEndCap;

		// generate faces by looping through vertices and adding their index to faces.
		for (int i = 0; i < numSegments - 1; ++i)
		{
			bottomEndCap.indices.append(i);
			topEndCap.indices.append(numSegments + i);

			Face temp{ {i, i + 1, numSegments + i + 1, numSegments + i} };
			faces.append(temp);
		}
		bottomEndCap.indices.append(numSegments - 1);
		topEndCap.indices.append(numSegments + numSegments - 1);
		faces.append(bottomEndCap, topEndCap);
		
		const Face temp{ {numSegments, 0, numSegments + 1, numSegments + numSegments - 1} };
		faces.append(temp);

		WriteToFile(fileName);
	}

private:
	void WriteToFile(G3D::String& fileName)
	{
		// write the header for the file
		G3D::TextOutput modelFile("../data-files/model/" + fileName);

		modelFile.writeSymbol("OFF");
		modelFile.writeNewline();
		modelFile.writeSymbol("# procedurally generated model file");
		modelFile.writeNewlines(2);
		modelFile.pushIndent();

		// calculate the number of vertices, faces, and edges (edges aren't read [but a count is required], so they can be any arbitrary number)
		modelFile.writeNumber(vertices.length());
		modelFile.writeNumber(faces.length());
		modelFile.writeNumber((vertices.length() / 2) * 3);
		modelFile.writeNewline();

		// print out each vertex
		for (const auto& vert : vertices)
		{
			modelFile.writeNumber(vert.x);
			modelFile.writeNumber(vert.y);
			modelFile.writeNumber(vert.z);
			modelFile.writeNewline();
		}

		// print out each face
		for (const auto& face : faces)
		{
			modelFile.writeNumber(face.indices.length()); // print the number of verts for this face
			for (int i = face.indices.lastIndex(); i >= 0; --i ) // print out the vertex indices for each face
			{
				modelFile.writeNumber(face.indices[i]);
			}

			// print out the color for this vertex (white)
			modelFile.writeNumber(255);
			modelFile.writeNumber(255);
			modelFile.writeNumber(255);

			modelFile.writeNewline();
		}

		modelFile.commit();
	}
};
