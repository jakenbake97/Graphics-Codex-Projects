#include <string>
#include <G3D-base/TextOutput.h>

class StairGenerator
{
private:
public:

	/** Generates a scene file containing a staircase by writing a series of strings to the file*/
	static void GenerateStairScene()
	{
		// Find and open the file
		G3D::TextOutput sceneFile("../data-files/scene/Staircase.Scene.Any");

		// generate File Header
		sceneFile.writeSymbols("//", "-*-", "c++", "-*-");
		sceneFile.writeNewline();

		sceneFile.writeSymbols("{");
		sceneFile.writeNewline();

		sceneFile.pushIndent();
		sceneFile.writeSymbol("name = \"Staircase\";");
		sceneFile.writeNewline();

		// generate models section
		sceneFile.printf("models = {");
		sceneFile.writeNewline();
		sceneFile.pushIndent();
		
		sceneFile.printf("stairCube = ArticulatedModel::Specification {");
		sceneFile.writeNewline();
		sceneFile.pushIndent();
		
		sceneFile.printf("filename = \"model/crate/crate.obj\";");
		sceneFile.writeNewline();
		sceneFile.printf("preprocess = {");
		sceneFile.writeNewline();
		sceneFile.pushIndent();
		
		sceneFile.printf("setMaterial(all(), \"../data-files/texture/woodGrain.jpg\");");
		sceneFile.writeNewline();
		

		sceneFile.printf("transformGeometry(all(), Matrix4::scale(2, 0.5, 1));");
		sceneFile.writeNewline();

		sceneFile.popIndent();
		sceneFile.writeSymbol("};");
		sceneFile.writeNewline();

		sceneFile.popIndent();
		sceneFile.writeSymbol("};");
		sceneFile.writeNewline();

		sceneFile.popIndent();
		sceneFile.writeSymbol("};");
		sceneFile.writeNewlines(2);


		// create entities section
		sceneFile.printf("entities = {");
		sceneFile.writeNewline();
		sceneFile.pushIndent();

		sceneFile.printf("skybox = Skybox {texture = \"cubemap/whiteroom/whiteroom-*.png\"};");
		sceneFile.writeNewlines(2);

		sceneFile.printf("sun = Light {");
		sceneFile.writeNewline();
		sceneFile.pushIndent();

		sceneFile.printf("attenuation = (0,0,1);");
		sceneFile.writeNewline();

		sceneFile.printf("bulbPower = Power3(4e+006);");
		sceneFile.writeNewline();

		sceneFile.printf("frame = CFrame::fromXYZYPRDegrees(-15, 207, -41, -164, -77, 77);");
		sceneFile.writeNewline();

		sceneFile.printf("shadowMapSize = Vector2int16(2048, 2048);");
		sceneFile.writeNewline();

		sceneFile.printf("spotHalfAngleDegrees = 5;");
		sceneFile.writeNewline();

		sceneFile.printf("rectangular = true;");
		sceneFile.writeNewline();

		sceneFile.printf("type = \"SPOT\";");
		sceneFile.writeNewline();

		sceneFile.popIndent();
		sceneFile.writeSymbol("};");
		sceneFile.writeNewline();

		sceneFile.printf("camera = Camera {");
		sceneFile.writeNewline();
		sceneFile.pushIndent();

		sceneFile.printf("frame = CFrame::fromXYZYPRDegrees(0, 0, 5);");
		sceneFile.writeNewline();

		sceneFile.popIndent();
		sceneFile.writeSymbol("};");
		sceneFile.writeNewline();

		// create the looped instances of the stair cubes
		for (int i = 0; i < 50; ++i)
		{
			// step name
			sceneFile.printf("step");
			sceneFile.writeNumber(i);
			sceneFile.printf(" = VisibleEntity {");
			sceneFile.writeNewline();

			sceneFile.pushIndent();
			sceneFile.printf("model = \"stairCube\";");
			sceneFile.writeNewline();

			double rads = G3D::toRadians(i * -14.4);
			
			sceneFile.printf("frame = CFrame::fromXYZYPRDegrees(");
			sceneFile.writeNumber(cos(rads) * 3); // x
			sceneFile.writeSymbol(",");
			sceneFile.writeNumber(i * 0.5); // y
			sceneFile.writeSymbol(",");
			sceneFile.writeNumber(sin(rads) * 3); // z
			sceneFile.writeSymbol(",");
			sceneFile.writeNumber(i * 14.4);// yaw
			sceneFile.writeSymbol(",");
			sceneFile.writeNumber(0); // pitch
			sceneFile.writeSymbol(",");
			sceneFile.writeNumber(0); // roll
			sceneFile.writeSymbol(");");
			
			sceneFile.writeNewline();

			sceneFile.popIndent();
			sceneFile.writeSymbol("};");
			sceneFile.writeNewlines(2);
		}

		sceneFile.popIndent();
		sceneFile.writeSymbol("};");
		sceneFile.writeNewline();
		
		// commit text to the file
		sceneFile.popIndent();
		sceneFile.writeSymbol("};");
		sceneFile.writeNewline();
		
		sceneFile.commit();
	}
};