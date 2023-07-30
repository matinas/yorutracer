#ifndef CAMERA_H
#define CAMERA_H

#include "math\point.h"
#include "math\vector.h"
#include "math\matrix\matrix3x3.h"
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
		Camera(yorumathpoint::Point3f origin, yorumathvector::Vector3f up, yorumathvector::Vector3f forward);
		Camera(yorumathpoint::Point3f origin, yorumathvector::Vector3f up, yorumathvector::Vector3f forward, float near, float far, float fov);
		Camera(yorumathpoint::Point3f origin, yorumathvector::Vector3f up, yorumathvector::Vector3f forward, float near, float far, float fovh, float fovv);
		Camera(yorumathpoint::Point3f origin, yorumathvector::Vector3f up, yorumathvector::Vector3f forward, float near, float far, Viewport viewport);

		yorumathpoint::Point3f getOrigin() const;
		yorumathvector::Vector3f getUp() const;
		yorumathvector::Vector3f getForward() const;
		float getNear() const;
		float getFar() const;
		float getFovH() const;
		float getFovV() const;
		Viewport getViewport() const;
		math::Matrix3x3* getViewMatrix() const;

		bool isInsideVolume(const yorumathpoint::Point3f& p); // checks whether the point is in fron the camera (inside the camera's projection volume)

		void lookAt(const yorumathpoint::Point3f& target);

	private:
		yorumathpoint::Point3f origin;
		yorumathvector::Vector3f up, forward;

		float near, far;  // near and far planes for the camera viewing frustum
		float fovh, fovv; // horizontal and vertical FOV, respectively

		Viewport viewport;

		math::Matrix3x3* viewMatrix;

		void setProjectionPlaneSettings(float near, float far, float fovh, float fovv);
		void setProjectionPlaneSettings(float near, float far, Viewport viewport);

		static Viewport calculateViewport(float near, float fovh, float fovv);
		static double calculateFOV(float near, Viewport viewport, FOVType type);
	};
}}

#endif
