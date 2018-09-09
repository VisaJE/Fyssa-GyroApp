#pragma once
/***********************************************************************
* THIS FILE HAS BEEN GENERATED BY WBRES TOOL. DO NOT TRY TO CHANGE IT. *
***********************************************************************/
// Copyright (c) Suunto Oy 2014 - 2017. All rights reserved.

#include "whiteboard/Identifiers.h"
#include "whiteboard/ParameterList.h"
#include "whiteboard/Result.h"
#include "whiteboard/ResourceClient.h"

#include "whiteboard/builtinTypes/Array.h"
#include "whiteboard/builtinTypes/ByteStream.h"
#include "whiteboard/builtinTypes/Date.h"
#include "whiteboard/builtinTypes/DateTime.h"
#include "whiteboard/builtinTypes/Optional.h"
#include "whiteboard/builtinTypes/Structures.h"
#include "whiteboard/builtinTypes/Time.h"
#include "whiteboard/builtinTypes/Timestamp.h"
#include "whiteboard/builtinTypes/TypedEnum.h"
#include "whiteboard/builtinTypes/Vector2D.h"
#include "whiteboard/builtinTypes/Vector3D.h"
#include "whiteboard/builtinTypes/WrapperFor32BitPointer.h"

#define WB_RESOURCE_VALUE(whiteboardId, localResourceId, executionContextId) \
    static_cast<whiteboard::ResourceId::Value>( \
        (static_cast<uint32>(localResourceId) << 16) | \
        (static_cast<uint32>(whiteboardId) << 8) | \
        (static_cast<uint32>(executionContextId) << 4) | \
        (static_cast<uint32>(whiteboard::ID_INVALID_RESOURCE_INSTANCE)))


#include "../wb-resources/resources.h"

#define WB_EXEC_CTX_APPLICATION                  static_cast<whiteboard::ExecutionContextId>(0)
#define WB_EXEC_CTX_MEAS                         static_cast<whiteboard::ExecutionContextId>(1)

#define WB_EXEC_CTX_APPLICATION_STACKSIZE        768
#define WB_EXEC_CTX_APPLICATION_PRIORITY         WB_THREAD_PRIORITY_NORMAL

namespace WB_RES {

struct WB_ALIGN(4) HeadingValue;
struct WB_ALIGN(4) FyssaGyroConfig;
struct WB_ALIGN(4) PositionValue;
struct WB_ALIGN(4) FyssaAccConfig;

struct WB_ALIGN(4) HeadingValue
{
	// Structure type identification and serialization
	typedef int Structure;
	static const whiteboard::LocalDataTypeId DATA_TYPE_ID = 25600;

	WB_ALIGN(4) float frontx;
	WB_ALIGN(4) float fronty;
	WB_ALIGN(4) float frontz;
	WB_ALIGN(4) float topx;
	WB_ALIGN(4) float topy;
	WB_ALIGN(4) float topz;
};

struct WB_ALIGN(4) FyssaGyroConfig
{
	// Structure type identification and serialization
	typedef int Structure;
	static const whiteboard::LocalDataTypeId DATA_TYPE_ID = 25601;

	WB_ALIGN(4) uint32 rate;
	WB_ALIGN(4) float threshold;
};

struct WB_ALIGN(4) PositionValue
{
	// Structure type identification and serialization
	typedef int Structure;
	static const whiteboard::LocalDataTypeId DATA_TYPE_ID = 25602;

	WB_ALIGN(4) float x;
	WB_ALIGN(4) float y;
	WB_ALIGN(4) float z;
};

struct WB_ALIGN(4) FyssaAccConfig
{
	// Structure type identification and serialization
	typedef int Structure;
	static const whiteboard::LocalDataTypeId DATA_TYPE_ID = 25603;

	WB_ALIGN(4) uint32 rate;
	WB_ALIGN(4) float threshold;
	WB_ALIGN(1) bool filter;
};

namespace LOCAL 
{

struct ROOT;

struct FYSSA;

struct FYSSA_GYRO
{
	static const whiteboard::ExecutionContextId EXECUTION_CONTEXT = WB_EXEC_CTX_MEAS;
	static const whiteboard::ResourceId::Value ID = WB_RESOURCE_VALUE(0, 25600, EXECUTION_CONTEXT);
	static const whiteboard::LocalResourceId LID = 25600;

	struct GET
	{
		typedef whiteboard::StronglyTypedResult<const HeadingValue&, whiteboard::HTTP_CODE_OK> HTTP_CODE_OK;
		typedef whiteboard::StronglyTypedResult<const whiteboard::NoType&, whiteboard::HTTP_CODE_NO_CONTENT> HTTP_CODE_NO_CONTENT;

		struct Parameters
		{
			static const whiteboard::ParameterIndex NUMBER_OF_PARAMETERS = 0;
		};

		/** Compile time type checking */
		inline static void typeCheck()
		{
		}
	};

	struct SUBSCRIBE
	{
		typedef whiteboard::StronglyTypedResult<const whiteboard::NoType&, whiteboard::HTTP_CODE_OK> HTTP_CODE_OK;

		struct Parameters
		{
			static const whiteboard::ParameterIndex NUMBER_OF_PARAMETERS = 0;
		};

		/** Compile time type checking */
		inline static void typeCheck()
		{
		}
	};

	struct EVENT
	{
		typedef HeadingValue NotificationType;
		typedef const NotificationType& ConstReferenceNotificationType;

		struct Parameters
		{
			static const whiteboard::ParameterIndex NUMBER_OF_PARAMETERS = 0;
		};

		/** Compile time type checking */
		inline static void typeCheck(
			const whiteboard::Api::OptionalParameter<ConstReferenceNotificationType>&)
		{
		}
	};

	struct UNSUBSCRIBE
	{
		typedef whiteboard::StronglyTypedResult<const whiteboard::NoType&, whiteboard::HTTP_CODE_OK> HTTP_CODE_OK;

		struct Parameters
		{
			static const whiteboard::ParameterIndex NUMBER_OF_PARAMETERS = 0;
		};

		/** Compile time type checking */
		inline static void typeCheck()
		{
		}
	};
};

struct FYSSA_GYRO_FYSSAGYROCONFIG
{
	static const whiteboard::ExecutionContextId EXECUTION_CONTEXT = WB_EXEC_CTX_MEAS;
	static const whiteboard::ResourceId::Value ID = WB_RESOURCE_VALUE(0, 25601, EXECUTION_CONTEXT);
	static const whiteboard::LocalResourceId LID = 25601;

	struct PUT
	{
		typedef whiteboard::StronglyTypedResult<const whiteboard::NoType&, whiteboard::HTTP_CODE_OK> HTTP_CODE_OK;
		typedef whiteboard::StronglyTypedResult<const whiteboard::NoType&, whiteboard::HTTP_CODE_BAD_REQUEST> HTTP_CODE_BAD_REQUEST;

		struct Parameters
		{
			struct FYSSAGYROCONFIG
			{
				static const whiteboard::ParameterIndex Index = 0;

				typedef FyssaGyroConfig Type;
				typedef const Type& ConstReferenceType;
			};

			typedef FYSSAGYROCONFIG Parameter1;

			static const whiteboard::ParameterIndex NUMBER_OF_PARAMETERS = 1;
		};

		/** Reference wrapper for strongly typed parameter list for /Fyssa/Gyro/FyssaGyroConfig */
		class ParameterListRef
		{
		private:
			/** Prevent use of default constructor */
			ParameterListRef() DELETED;

			/** Prevent use of copy constructor */
			ParameterListRef(const ParameterListRef&) DELETED;

			/** Prevent use of assignment operator */
			const ParameterListRef& operator=(const ParameterListRef&) DELETED;

		public:
			/** Constructor that initializes this class from existing parameter list
			*
			* @param rParameterList Reference to parameter list that contains untyped parameters
			*/
			inline ParameterListRef(const whiteboard::ParameterList& rParameterList)
				: mrParameterList(rParameterList)
			{
			}

			/** Gets FYSSAGYROCONFIG parameter value
			*
			* @return Current parameter value
			*/
			inline Parameters::FYSSAGYROCONFIG::ConstReferenceType getFyssaGyroConfig() const
			{
				return mrParameterList[Parameters::FYSSAGYROCONFIG::Index].convertTo<Parameters::FYSSAGYROCONFIG::ConstReferenceType>();
			}

		private:
			/** Reference to actual parameter list */
			const whiteboard::ParameterList& mrParameterList;
		};

		/** Compile time type checking */
		inline static void typeCheck(
			Parameters::FYSSAGYROCONFIG::ConstReferenceType)
		{
		}
	};
};

struct FYSSA_IMU
{
	static const whiteboard::ExecutionContextId EXECUTION_CONTEXT = WB_EXEC_CTX_MEAS;
	static const whiteboard::ResourceId::Value ID = WB_RESOURCE_VALUE(0, 25602, EXECUTION_CONTEXT);
	static const whiteboard::LocalResourceId LID = 25602;

	struct GET
	{
		typedef whiteboard::StronglyTypedResult<const PositionValue&, whiteboard::HTTP_CODE_OK> HTTP_CODE_OK;
		typedef whiteboard::StronglyTypedResult<const whiteboard::NoType&, whiteboard::HTTP_CODE_NO_CONTENT> HTTP_CODE_NO_CONTENT;

		struct Parameters
		{
			static const whiteboard::ParameterIndex NUMBER_OF_PARAMETERS = 0;
		};

		/** Compile time type checking */
		inline static void typeCheck()
		{
		}
	};

	struct SUBSCRIBE
	{
		typedef whiteboard::StronglyTypedResult<const whiteboard::NoType&, whiteboard::HTTP_CODE_OK> HTTP_CODE_OK;

		struct Parameters
		{
			static const whiteboard::ParameterIndex NUMBER_OF_PARAMETERS = 0;
		};

		/** Compile time type checking */
		inline static void typeCheck()
		{
		}
	};

	struct EVENT
	{
		typedef PositionValue NotificationType;
		typedef const NotificationType& ConstReferenceNotificationType;

		struct Parameters
		{
			static const whiteboard::ParameterIndex NUMBER_OF_PARAMETERS = 0;
		};

		/** Compile time type checking */
		inline static void typeCheck(
			const whiteboard::Api::OptionalParameter<ConstReferenceNotificationType>&)
		{
		}
	};

	struct UNSUBSCRIBE
	{
		typedef whiteboard::StronglyTypedResult<const whiteboard::NoType&, whiteboard::HTTP_CODE_OK> HTTP_CODE_OK;

		struct Parameters
		{
			static const whiteboard::ParameterIndex NUMBER_OF_PARAMETERS = 0;
		};

		/** Compile time type checking */
		inline static void typeCheck()
		{
		}
	};
};

struct FYSSA_IMU_FYSSAACCCONFIG
{
	static const whiteboard::ExecutionContextId EXECUTION_CONTEXT = WB_EXEC_CTX_MEAS;
	static const whiteboard::ResourceId::Value ID = WB_RESOURCE_VALUE(0, 25603, EXECUTION_CONTEXT);
	static const whiteboard::LocalResourceId LID = 25603;

	struct PUT
	{
		typedef whiteboard::StronglyTypedResult<const whiteboard::NoType&, whiteboard::HTTP_CODE_OK> HTTP_CODE_OK;
		typedef whiteboard::StronglyTypedResult<const whiteboard::NoType&, whiteboard::HTTP_CODE_BAD_REQUEST> HTTP_CODE_BAD_REQUEST;

		struct Parameters
		{
			struct FYSSAACCCONFIG
			{
				static const whiteboard::ParameterIndex Index = 0;

				typedef FyssaAccConfig Type;
				typedef const Type& ConstReferenceType;
			};

			typedef FYSSAACCCONFIG Parameter1;

			static const whiteboard::ParameterIndex NUMBER_OF_PARAMETERS = 1;
		};

		/** Reference wrapper for strongly typed parameter list for /Fyssa/Imu/FyssaAccConfig */
		class ParameterListRef
		{
		private:
			/** Prevent use of default constructor */
			ParameterListRef() DELETED;

			/** Prevent use of copy constructor */
			ParameterListRef(const ParameterListRef&) DELETED;

			/** Prevent use of assignment operator */
			const ParameterListRef& operator=(const ParameterListRef&) DELETED;

		public:
			/** Constructor that initializes this class from existing parameter list
			*
			* @param rParameterList Reference to parameter list that contains untyped parameters
			*/
			inline ParameterListRef(const whiteboard::ParameterList& rParameterList)
				: mrParameterList(rParameterList)
			{
			}

			/** Gets FYSSAACCCONFIG parameter value
			*
			* @return Current parameter value
			*/
			inline Parameters::FYSSAACCCONFIG::ConstReferenceType getFyssaAccConfig() const
			{
				return mrParameterList[Parameters::FYSSAACCCONFIG::Index].convertTo<Parameters::FYSSAACCCONFIG::ConstReferenceType>();
			}

		private:
			/** Reference to actual parameter list */
			const whiteboard::ParameterList& mrParameterList;
		};

		/** Compile time type checking */
		inline static void typeCheck(
			Parameters::FYSSAACCCONFIG::ConstReferenceType)
		{
		}
	};
};



} // namespace LOCAL 

} // namespace WB_RES
