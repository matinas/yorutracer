#include <iostream>
#include <cmath>
#include <string>

#include "renderer\camera.h"
#include "utils.h"

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
	}

	Camera::Camera(yoru::math::Point3d origin, yoru::math::Vector3d up, yoru::math::Vector3d forward) : origin(origin), up(up), forward(forward),
																										near(DefaultNearPlane), far(DefaultFarPlane),
																										fovh(DefaultFovH), fovv(DefaultFovV)
	{
		this->viewport = calculateViewport(this->near, this->fovh, this->fovv);
	}

	Camera::Camera(yoru::math::Point3d origin, yoru::math::Vector3d up, yoru::math::Vector3d forward, float near, float far, float fov) : origin(origin), up(up), forward(forward)
	{
		setProjectionPlaneSettings(near, far, fov, fov);
	}

	Camera::Camera(yoru::math::Point3d origin, yoru::math::Vector3d up, yoru::math::Vector3d forward, float near, float far, float fovh, float fovv) : origin(origin), up(up), forward(forward)
	{
		setProjectionPlaneSettings(near, far, fovh, fovv);
	}

	Camera::Camera(yoru::math::Point3d origin, yoru::math::Vector3d up, yoru::math::Vector3d forward, float near, float far, Viewport viewport) : origin(origin), up(up), forward(forward)
	{
		setProjectionPlaneSettings(near, far, viewport);
	}

	math::Point3d Camera::getOrigin()
	{
		return this->origin;
	}

	math::Vector3d Camera::getUp()
	{
		return this->up;
	}

	math::Vector3d Camera::getForward()
	{
		return this->forward;
	}

	float Camera::getNear()
	{
		return this->near;
	}

	float Camera::getFar()
	{
		return this->far;
	}

	float Camera::getFovH()
	{
		return this->fovh;
	}

	float Camera::getFovV()
	{
		return this->fovv;
	}

	Viewport Camera::getViewport()
	{
		return this->viewport;
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

		std::cout << "Viewport trying to set is (" << viewport.getWidth() << ", " << viewport.getHeight() << ")" << '\n';

		this->viewport = Viewport(viewport.getWidth() <= 0 ? Camera::DefaultViewportSize : viewport.getWidth(),
								  viewport.getHeight() <= 0 ? Camera::DefaultViewportSize : viewport.getHeight());

		std::cout << "Viewport to actually be set is (" << this->viewport.getWidth() << ", " << this->viewport.getHeight() << ")" << '\n';

		this->fovh = calculateFOV(near, this->viewport, FOVType::FOVH);
		std::cout << "FOVH is " << this->fovh << '\n';
		this->fovv = calculateFOV(near, this->viewport, FOVType::FOVV);
		std::cout << "FOVV is " << this->fovv << '\n';
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