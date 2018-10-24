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
#include "../movesense_types/resources.h"

#define WB_EXEC_CTX_APPLICATION                  static_cast<whiteboard::ExecutionContextId>(0)
#define WB_EXEC_CTX_MEAS                         static_cast<whiteboard::ExecutionContextId>(1)

namespace WB_RES {

struct DebugLevelValues
{
	static const whiteboard::LocalDataTypeId DATA_TYPE_ID = 18433;

	enum Type
	{
		FATAL = 0,
		ERROR = 1,
		WARNING = 2,
		INFO = 3,
		VERBOSE = 4
	};
};
typedef whiteboard::TypedEnum<DebugLevelValues, DebugLevelValues::Type, int32> DebugLevel;

struct WB_ALIGN(1) DebugMessageConfig;
struct WB_ALIGN(4) DebugMessage;
struct WB_ALIGN(4) DebugLogQuery;
struct WB_ALIGN(4) DebugLogConfig;
struct WB_ALIGN(4) DebugLogResult;

struct WB_ALIGN(1) DebugMessageConfig
{
	// Structure type identification and serialization
	typedef int Structure;
	static const whiteboard::LocalDataTypeId DATA_TYPE_ID = 18432;

	WB_ALIGN(1) whiteboard::Optional< bool > systemMessages;
	WB_ALIGN(1) whiteboard::Optional< bool > userMessages;
};

struct WB_ALIGN(4) DebugMessage
{
	// Structure type identification and serialization
	typedef int Structure;
	static const whiteboard::LocalDataTypeId DATA_TYPE_ID = 18434;

	WB_ALIGN(4) uint32 timestamp;
	WB_ALIGN(4) DebugLevel level;
	WB_ALIGN(4) whiteboard::WrapperFor32BitPointer<const char> tag;
	WB_ALIGN(4) whiteboard::WrapperFor32BitPointer<const char> message;
};

struct WB_ALIGN(4) DebugLogQuery
{
	// Structure type identification and serialization
	typedef int Structure;
	static const whiteboard::LocalDataTypeId DATA_TYPE_ID = 18435;

	WB_ALIGN(4) uint32 timestamp;
	WB_ALIGN(2) uint16 count;
};

struct WB_ALIGN(4) DebugLogConfig
{
	// Structure type identification and serialization
	typedef int Structure;
	static const whiteboard::LocalDataTypeId DATA_TYPE_ID = 18436;

	WB_ALIGN(4) DebugLevel minimalLevel;
};

struct WB_ALIGN(4) DebugLogResult
{
	// Structure type identification and serialization
	typedef int Structure;
	static const whiteboard::LocalDataTypeId DATA_TYPE_ID = 18437;

	WB_ALIGN(4) whiteboard::Array< DebugMessage > messages;
};

namespace LOCAL 
{

struct ROOT;

struct SYSTEM;

struct SYSTEM_DEBUG;

struct SYSTEM_DEBUG_CONFIG
{
	static const whiteboard::ExecutionContextId EXECUTION_CONTEXT = WB_EXEC_CTX_APPLICATION;
	static const whiteboard::ResourceId::Value ID = WB_RESOURCE_VALUE(0, 18432, EXECUTION_CONTEXT);
	static const whiteboard::LocalResourceId LID = 18432;

	struct GET
	{
		typedef whiteboard::StronglyTypedResult<const DebugMessageConfig&, whiteboard::HTTP_CODE_OK> HTTP_CODE_OK;

		struct Parameters
		{
			static const whiteboard::ParameterIndex NUMBER_OF_PARAMETERS = 0;
		};

		/** Compile time type checking */
		inline static void typeCheck()
		{
		}
	};

	struct PUT
	{
		typedef whiteboard::StronglyTypedResult<const whiteboard::NoType&, whiteboard::HTTP_CODE_OK> HTTP_CODE_OK;

		struct Parameters
		{
			struct CONFIG
			{
				static const whiteboard::ParameterIndex Index = 0;

				typedef DebugMessageConfig Type;
				typedef const Type& ConstReferenceType;
			};

			typedef CONFIG Parameter1;

			static const whiteboard::ParameterIndex NUMBER_OF_PARAMETERS = 1;
		};

		/** Reference wrapper for strongly typed parameter list for /System/Debug/Config */
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

			/** Gets CONFIG parameter value
			*
			* @return Current parameter value
			*/
			inline Parameters::CONFIG::ConstReferenceType getConfig() const
			{
				return mrParameterList[Parameters::CONFIG::Index].convertTo<Parameters::CONFIG::ConstReferenceType>();
			}

		private:
			/** Reference to actual parameter list */
			const whiteboard::ParameterList& mrParameterList;
		};

		/** Compile time type checking */
		inline static void typeCheck(
			Parameters::CONFIG::ConstReferenceType)
		{
		}
	};
};

struct SYSTEM_DEBUG_LOG
{
	static const whiteboard::ExecutionContextId EXECUTION_CONTEXT = WB_EXEC_CTX_APPLICATION;
	static const whiteboard::ResourceId::Value ID = WB_RESOURCE_VALUE(0, 18433, EXECUTION_CONTEXT);
	static const whiteboard::LocalResourceId LID = 18433;

	struct GET
	{
		typedef whiteboard::StronglyTypedResult<const DebugLogResult&, whiteboard::HTTP_CODE_OK> HTTP_CODE_OK;
		typedef whiteboard::StronglyTypedResult<const whiteboard::NoType&, whiteboard::HTTP_CODE_NO_CONTENT> HTTP_CODE_NO_CONTENT;

		struct Parameters
		{
			struct PARAMS
			{
				static const whiteboard::ParameterIndex Index = 0;

				typedef DebugLogQuery Type;
				typedef const Type& ConstReferenceType;
			};

			typedef PARAMS Parameter1;

			static const whiteboard::ParameterIndex NUMBER_OF_PARAMETERS = 1;
		};

		/** Reference wrapper for strongly typed parameter list for /System/Debug/Log */
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

			/** Gets PARAMS parameter value
			*
			* @return Current parameter value
			*/
			inline Parameters::PARAMS::ConstReferenceType getParams() const
			{
				return mrParameterList[Parameters::PARAMS::Index].convertTo<Parameters::PARAMS::ConstReferenceType>();
			}

		private:
			/** Reference to actual parameter list */
			const whiteboard::ParameterList& mrParameterList;
		};

		/** Compile time type checking */
		inline static void typeCheck(
			Parameters::PARAMS::ConstReferenceType)
		{
		}
	};
};

struct SYSTEM_DEBUG_LOG_CONFIG
{
	static const whiteboard::ExecutionContextId EXECUTION_CONTEXT = WB_EXEC_CTX_APPLICATION;
	static const whiteboard::ResourceId::Value ID = WB_RESOURCE_VALUE(0, 18434, EXECUTION_CONTEXT);
	static const whiteboard::LocalResourceId LID = 18434;

	struct GET
	{
		typedef whiteboard::StronglyTypedResult<const DebugLogConfig&, whiteboard::HTTP_CODE_OK> HTTP_CODE_OK;

		struct Parameters
		{
			static const whiteboard::ParameterIndex NUMBER_OF_PARAMETERS = 0;
		};

		/** Compile time type checking */
		inline static void typeCheck()
		{
		}
	};

	struct PUT
	{
		typedef whiteboard::StronglyTypedResult<const whiteboard::NoType&, whiteboard::HTTP_CODE_OK> HTTP_CODE_OK;

		struct Parameters
		{
			struct CONFIG
			{
				static const whiteboard::ParameterIndex Index = 0;

				typedef DebugLogConfig Type;
				typedef const Type& ConstReferenceType;
			};

			typedef CONFIG Parameter1;

			static const whiteboard::ParameterIndex NUMBER_OF_PARAMETERS = 1;
		};

		/** Reference wrapper for strongly typed parameter list for /System/Debug/Log/Config */
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

			/** Gets CONFIG parameter value
			*
			* @return Current parameter value
			*/
			inline Parameters::CONFIG::ConstReferenceType getConfig() const
			{
				return mrParameterList[Parameters::CONFIG::Index].convertTo<Parameters::CONFIG::ConstReferenceType>();
			}

		private:
			/** Reference to actual parameter list */
			const whiteboard::ParameterList& mrParameterList;
		};

		/** Compile time type checking */
		inline static void typeCheck(
			Parameters::CONFIG::ConstReferenceType)
		{
		}
	};
};

struct SYSTEM_DEBUG_LEVEL
{
	static const whiteboard::ExecutionContextId EXECUTION_CONTEXT = WB_EXEC_CTX_APPLICATION;
	static const whiteboard::ResourceId::Value ID = WB_RESOURCE_VALUE(0, 18435, EXECUTION_CONTEXT);
	static const whiteboard::LocalResourceId LID = 18435;

	struct SUBSCRIBE
	{
		typedef whiteboard::StronglyTypedResult<const whiteboard::NoType&, whiteboard::HTTP_CODE_OK> HTTP_CODE_OK;

		struct Parameters
		{
			struct LEVEL
			{
				static const whiteboard::ParameterIndex Index = 0;

				typedef DebugLevel Type;
				typedef Type ConstReferenceType;
			};

			typedef LEVEL Parameter1;

			static const whiteboard::ParameterIndex NUMBER_OF_PARAMETERS = 1;
		};

		/** Reference wrapper for strongly typed parameter list for /System/Debug/{Level} */
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

			/** Gets LEVEL parameter value
			*
			* @return Current parameter value
			*/
			inline Parameters::LEVEL::ConstReferenceType getLevel() const
			{
				return mrParameterList[Parameters::LEVEL::Index].convertTo<Parameters::LEVEL::ConstReferenceType>();
			}

		private:
			/** Reference to actual parameter list */
			const whiteboard::ParameterList& mrParameterList;
		};

		/** Compile time type checking */
		inline static void typeCheck(
			Parameters::LEVEL::ConstReferenceType)
		{
		}
	};

	struct EVENT
	{
		typedef DebugMessage NotificationType;
		typedef const NotificationType& ConstReferenceNotificationType;

		struct Parameters
		{
			struct LEVEL
			{
				static const whiteboard::ParameterIndex Index = 0;

				typedef DebugLevel Type;
				typedef Type ConstReferenceType;
			};

			typedef LEVEL Parameter1;

			static const whiteboard::ParameterIndex NUMBER_OF_PARAMETERS = 1;
		};

		/** Reference wrapper for strongly typed parameter list for /System/Debug/{Level} */
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

			/** Checks whether optional parameter LEVEL has a value
			*
			* @return A value indicating whether the parameter has a value
			*/
			inline bool hasLevel() const
			{
				if (mrParameterList.getNumberOfParameters() <= Parameters::LEVEL::Index)
				{
					return false;
				}

				return mrParameterList[Parameters::LEVEL::Index].getType() != whiteboard::WB_TYPE_NONE;
			}

			/** Gets LEVEL parameter value
			*
			* @return Current parameter value
			*/
			inline Parameters::LEVEL::ConstReferenceType getLevel() const
			{
				return mrParameterList[Parameters::LEVEL::Index].convertTo<Parameters::LEVEL::ConstReferenceType>();
			}

		private:
			/** Reference to actual parameter list */
			const whiteboard::ParameterList& mrParameterList;
		};

		/** Compile time type checking */
		inline static void typeCheck(
			const whiteboard::Api::OptionalParameter<ConstReferenceNotificationType>&,
			const whiteboard::Api::OptionalParameter<Parameters::LEVEL::ConstReferenceType>& = whiteboard::NoType::NoValue)
		{
		}
	};

	struct UNSUBSCRIBE
	{
		typedef whiteboard::StronglyTypedResult<const whiteboard::NoType&, whiteboard::HTTP_CODE_OK> HTTP_CODE_OK;

		struct Parameters
		{
			struct LEVEL
			{
				static const whiteboard::ParameterIndex Index = 0;

				typedef DebugLevel Type;
				typedef Type ConstReferenceType;
			};

			typedef LEVEL Parameter1;

			static const whiteboard::ParameterIndex NUMBER_OF_PARAMETERS = 1;
		};

		/** Reference wrapper for strongly typed parameter list for /System/Debug/{Level} */
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

			/** Gets LEVEL parameter value
			*
			* @return Current parameter value
			*/
			inline Parameters::LEVEL::ConstReferenceType getLevel() const
			{
				return mrParameterList[Parameters::LEVEL::Index].convertTo<Parameters::LEVEL::ConstReferenceType>();
			}

		private:
			/** Reference to actual parameter list */
			const whiteboard::ParameterList& mrParameterList;
		};

		/** Compile time type checking */
		inline static void typeCheck(
			Parameters::LEVEL::ConstReferenceType)
		{
		}
	};
};



} // namespace LOCAL 

} // namespace WB_RES
