#include <iostream>
#include <cmath>
#include <string>

#include "renderer\camera.h"
#include "utils\utils.h"
#include "math\matrix\matrixfactory.h"

namespace yoru {
namespace renderer {

	const float Camera::DefaultNearPlane = 1.0f;
	const float Camera::DefaultFarPlane = 100.0f;
	const float Camera::DefaultFovH = 55.0f;
	const float Camera::DefaultFovV = 55.0f;
	const float Camera::DefaultViewportSize = 1.0;

	Camera::Camera() : origin(math::Point3d(0.0f, 0.0f, 0.0f)), up(math::Vector3d(0.0f, 1.0f, 0.0f)), forward(math::Vector3d(0.0f, 0.0f, 1.0f)),
					   near(DefaultNearPlane), far(DefaultFarPlane), fovh(DefaultFovH), fovv(DefaultFovV)
	{
		this->viewport = calculateViewport(this->near, this->fovh, this->fovv);
		this->viewMatrix = math::Matrix3x3::identity;
	}

	Camera::Camera(yoru::math::Point3d origin, yoru::math::Vector3d up, yoru::math::Vector3d forward) : origin(origin), up(up), forward(forward),
																										near(DefaultNearPlane), far(DefaultFarPlane),
																										fovh(DefaultFovH), fovv(DefaultFovV)
	{
		this->viewport = calculateViewport(this->near, this->fovh, this->fovv);
		this->viewMatrix = math::Matrix3x3::identity;
	}

	Camera::Camera(yoru::math::Point3d origin, yoru::math::Vector3d up, yoru::math::Vector3d forward, float near, float far, float fov) : origin(origin), up(up), forward(forward)
	{
		setProjectionPlaneSettings(near, far, fov, fov);

		this->viewMatrix = math::Matrix3x3::identity;
	}

	Camera::Camera(yoru::math::Point3d origin, yoru::math::Vector3d up, yoru::math::Vector3d forward, float near, float far, float fovh, float fovv) : origin(origin), up(up), forward(forward)
	{
		setProjectionPlaneSettings(near, far, fovh, fovv);

		this->viewMatrix = math::Matrix3x3::identity;
	}

	Camera::Camera(yoru::math::Point3d origin, yoru::math::Vector3d up, yoru::math::Vector3d forward, float near, float far, Viewport viewport) : origin(origin), up(up), forward(forward)
	{
		setProjectionPlaneSettings(near, far, viewport);

		this->viewMatrix = math::Matrix3x3::identity;
	}

	math::Point3d Camera::getOrigin() const
	{
		return this->origin;
	}

	math::Vector3d Camera::getUp() const
	{
		return this->up;
	}

	math::Vector3d Camera::getForward() const
	{
		return this->forward;
	}

	float Camera::getNear() const
	{
		return this->near;
	}

	float Camera::getFar() const
	{
		return this->far;
	}

	float Camera::getFovH() const
	{
		return this->fovh;
	}

	float Camera::getFovV() const
	{
		return this->fovv;
	}

	Viewport Camera::getViewport() const
	{
		return this->viewport;
	}

	math::Matrix3x3* Camera::getViewMatrix() const
	{
		return this->viewMatrix;
	}

	bool Camera::isInsideVolume(const math::Point3d& p)
	{
		// TODO: over-simplified version that assumes the camera is always at the origin pointing towards z+
		// we'll need to generalize this whenever we add support to place the camera at whatever position/direction

		// NOTE: another simple and more performant way of implementing this is to tackle it sooner, taking into account
		// only those t where t > Camera.near (discard negative roots/ts along the ray) when calculating the intersections between the ray and the scene's objects
		// the drawback is that it implies getting the camera info inside the ray intersection calculations somehow...

		// another similar way would be to store the roots t inside the RayIntersectionInfo in addition to the points
		// then when we check for hitInfo.hasHits() we can check whether those t values are valid (in front of Camera.near)

		return p.getZ() >= near;
	}

	void Camera::lookAt(const math::Point3d& target)
	{
		math::Vector3d forward = target - this->getOrigin();
		forward.normalize();

		math::Vector3d right = this->getUp().cross(forward);
		right.normalize();

		math::Vector3d up = forward.cross(right);
		up.normalize();

		// TODO: we still need to take into acount the eye/camera position as part of this matrix
		// for which we'll need to use 4x4 Matrix as it requires not only a rotation, but also a translation

		this->viewMatrix = math::MatrixFactory::getMatrix(right, up, forward); // this is the inverse (= transpose, as it's orthogonal) of the camera matrix
																			   // which contains the camera's reference system axis on each of its columns
	}

	void setPositiveNumericSetting(float&, float, float, std::string);
	void Camera::setProjectionPlaneSettings(float near, float far, float fovh, float fovv)
	{
		setPositiveNumericSetting(this->near, near, DefaultNearPlane, NAMEOF(near));
		setPositiveNumericSetting(this->far, far, DefaultFarPlane, NAMEOF(far));
		setPositiveNumericSetting(this->fovh, fovh, DefaultFovH, NAMEOF(fovh));
		setPositiveNumericSetting(this->fovv, fovv, DefaultFovV, NAMEOF(fovv));

		this->viewport = calculateViewport(this->near, this->fovh, this->fovv);
	}

	void Camera::setProjectionPlaneSettings(float near, float far, Viewport viewport)
	{
		setPositiveNumericSetting(this->near, near, DefaultNearPlane, NAMEOF(near));
		setPositiveNumericSetting(this->far, far, DefaultFarPlane, NAMEOF(far));

		this->viewport = Viewport(viewport.getWidth() <= 0 ? Camera::DefaultViewportSize : viewport.getWidth(),
								  viewport.getHeight() <= 0 ? Camera::DefaultViewportSize : viewport.getHeight());

		this->fovh = calculateFOV(near, this->viewport, FOVType::FOVH);
		this->fovv = calculateFOV(near, this->viewport, FOVType::FOVV);
	}

	void setPositiveNumericSetting(float& setting, float value, float default, std::string name)
	{
		if (value <= 0)
		{
			std::cout << "[Error] Setting " << name << " must be positive, so it will be set to the default value of " << default << '\n';
			setting = default;
		}
		else
		{
			setting = value;
		}
	}

	// calculates the viewport dimensions for the given fov (either horizontal or vertical) and distance d from the viewing
	// point, assuming that the distance between the viewing point and the viewport center equals d when tracing a perpendicular
	// line from viewport's center, and returns the resulting viewport
	Viewport Camera::calculateViewport(float d, float fovh, float fovv)
	{
		//    __Vw/2_________
		//    \      |      /
		//     \     |     /
		//    h \    | d  /
		//       \   |   /
		//        \  |  /
		//   	   \ | (angle=fov/2)
		//          \|/
		//
		// we know that cos=adj/hip, so we have that cos(fov/2)=d/hip, hence hip=d/cos(fov/2)
		// on the other hand we know that sin=op/hip, so sin(fov/2)=(Vw/2)/hip, hence Vw = 2 x hip x sin(fov/2)
		// substituting hip from the first equation: Vw = 2 x d x (sin(fov/2)/cos(fov/2))
		// as sin/cos=tg: Vw = 2 x d x tg(fov/2)

		double Vw = 2 * d * tan(utils::toRadians(fovh/2.0));
		double Vh = 2 * d * tan(utils::toRadians(fovv/2.0));

		return Viewport(Vw, Vh);
	}

	// infers the field of view (either horizontal or vertical) given the specified
	// viewport lies at a distance d from the viewing point
	double Camera::calculateFOV(float d, Viewport viewport, FOVType type)
	{
		double fov = 0.0f;
		switch (type)
		{
			case FOVType::FOVH:
				fov = 2 * atan(viewport.getWidth() * 0.5f / d);
				break;
			case FOVType::FOVV:
				fov = 2 * atan(viewport.getHeight() * 0.5f / d);
				break;
			default:
				std::cout << "Error: Unknown FOV type\n";
		}

		return utils::toDegrees(fov);
	}
}}