#ifndef CAMERA_H
#define CAMERA_H

#include "math\point3d.h"
#include "math\vector3d.h"
#include "renderer\viewport.h"

namespace yoru {
namespace renderer {

	enum FOVType
	{
		FOVH,
		FOVV
	};

	class Camera
	{
	public:
		static const float DefaultNearPlane, DefaultFarPlane, DefaultFovH, DefaultFovV, DefaultViewportSize;

		Camera();
		Camera(yoru::math::Point3d origin, yoru::math::Vector3d up, yoru::math::Vector3d forward);
		Camera(yoru::math::Point3d origin, yoru::math::Vector3d up, yoru::math::Vector3d forward, float near, float far, float fov);
		Camera(yoru::math::Point3d origin, yoru::math::Vector3d up, yoru::math::Vector3d forward, float near, float far, float fovh, float fovv);
		Camera(yoru::math::Point3d origin, yoru::math::Vector3d up, yoru::math::Vector3d forward, float near, float far, Viewport viewport);

		math::Point3d getOrigin();
		math::Vector3d getUp();
		math::Vector3d getForward();
		float getNear();
		float getFar();
		float getFovH();
		float getFovV();
		Viewport getViewport();

	private:
		math::Point3d origin;
		math::Vector3d up, forward;

		float near, far;  // near and far planes for the camera viewing frustum
		float fovh, fovv; // horizontal and vertical FOV, respectively

		Viewport viewport;

		void setProjectionPlaneSettings(float near, float far, float fovh, float fovv);
		void setProjectionPlaneSettings(float near, float far, Viewport viewport);

		static Viewport calculateViewport(float near, float fovh, float fovv);
		static double calculateFOV(float near, Viewport viewport, FOVType type);
	};
}}

#endif
