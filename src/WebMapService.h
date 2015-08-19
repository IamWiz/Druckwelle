#pragma once

#include "dwcore.h"

#include <string>
#include <vector>
#include <map>

namespace dw
{
	class WebMapService
	{
	public:

		struct GetMapRequest
		{
			struct BBox
			{
				double minX;
				double minY;
				double maxX;
				double maxY;
			};
			astring styles;
			astring crs;
			BBox bbox;
			int width;
			int height;

			DataType dataType;
		};

		class Layer
		{
		public:

			enum HandleGetMapRequestResult
			{
				HGMRR_OK,
				HGMRR_InvalidStyle,
				HGMRR_InvalidFormat,
				HGMRR_InvalidBBox,
				HGMRR_InvalidSRS,
				HGMRR_InternalError, // e.g. file corrupt/missing
			};

			virtual ~Layer() {};

			virtual bool Init(/* layerconfig */) { return true; };  // return true on successful init
 			virtual const char* GetName() const = 0;				// computer readable name (unique identification)
			virtual const char_t* GetTitle() const = 0;				// human readable name
			virtual const char_t* GetAbstract()  const { return NULL; };
			virtual const int GetFixedWidth() const { return 0; };
			virtual const int GetFixedHeight() const { return 0; };
			virtual const int GetMaxWidth() const { return 0; };
			virtual const int GetMaxHeight() const { return 0; };
			virtual const std::vector<DataType>& GetSuppordetFormats() const = 0;

			virtual HandleGetMapRequestResult HandleGetMapRequest(const WebMapService::GetMapRequest& gmr, u8* data) = 0;
		};

		typedef Layer* (*CreateLayer)();

		class LayerFactory
		{
		public:
			LayerFactory(const astring& layerName, const string& layerTitle, CreateLayer createLayer)
			{
				LayerDesc lDesc;
				lDesc.name = layerName;
				lDesc.title = layerTitle;
				lDesc.createLayer = createLayer;
				GetStaticLayers().push_back(lDesc);
			}

			static void CreateLayers(std::map<astring, Layer*>& layers /*, config*/);

		private:

			struct LayerDesc
			{
				astring name; // computer readable name (unique identification)
				string title; // human readable name
				CreateLayer createLayer;
			};

			static std::vector<LayerDesc>& GetStaticLayers()
			{
				static std::vector<LayerDesc>* layers = NULL;
				if (layers == NULL)
				{
					layers = new std::vector<LayerDesc>();
				}
				return *layers;
			}
		};

		WebMapService();

		int Start();
		void Stop();

		int HandleRequest(struct MHD_Connection* connection, const char* url, const char* method);
	private:

		int HandleGetMapRequest(struct MHD_Connection *connection, const astring& layers, ContentType contentType, struct GetMapRequest& gmr);

		std::map<astring, Layer*> availableLayers;
	};

	#define IMPLEMENT_WEBMAPSERVICE_LAYER(Class, Name, Title) \
		static WebMapService::Layer* Construct##LayerName() { return new Class(); } \
		WebMapService::LayerFactory Class##Factory(LayerName, LayerTitle, Construct##LayerName);
}