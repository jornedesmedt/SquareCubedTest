#pragma once

#include <ClientBase/IContent.h>

#include <vector>

namespace DefaultContent {
	class DefaultContent final : public Content::IContent {
		// Internal Content Entry
		struct ContentEntry {
			const std::string Type;
			const std::string Path;
			Content::IContentBase* C;

			ContentEntry(const char* type, std::string path, Content::IContentBase* c) :
				Type(type),
				Path(path),
				C(c)
			{}
		};

		// Storage of Content Entries
		std::vector<ContentEntry> m_ContentList;

	public: // Initialization/Uninitialization
		DefaultContent();
		~DefaultContent();

	private: // Internal Wrapped Utility Functions
		Content::IContentBase& GetContent(Content::IContentFactory &type, std::string path);

	public: // Content Utility Functions
		void ClearContent();
	};
}