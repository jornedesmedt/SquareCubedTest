#include "DefaultContent.h"
#include "DefaultContentLoader.h"

#include <algorithm>

namespace DefaultContent {
	// Factory to avoid including the big compiler-grinding-to-a-crawl file
	Content::IContent* LoadContent() { return new DefaultContent(); }

	// Initialization/Uninitialization

	DefaultContent::DefaultContent() :
		m_ContentList()
	{
	}

	DefaultContent::~DefaultContent() {
		ClearContent();
	}

	// Internal Wrapped Utility Functions

	Content::IContentBase& DefaultContent::GetContent(Content::IContentFactory &type, std::string path) {
		// Transform the string so we can avoid duplicates better
		std::transform(path.begin(), path.end(), path.begin(), ::tolower);

		// Check if it already exists, if yes return it
		for (ContentEntry &entry : m_ContentList) {
			// Same Type?
			if (entry.Type == type.GetTypeName()) {
				// Same Path?
				if (entry.Path == path) {
					// And Return it
					return *entry.C;
				}
			}
		}

		// Since it doesn't exist, create it
		ContentEntry contentEntry(
			type.GetTypeName(),
			path,
			type.New(path)
		);

		// Add it to the list
		m_ContentList.push_back(contentEntry);

		// Log it
		//m_Logger.LogInfo("Loaded new %s: %s", type.GetTypeName(), path.c_str());
		printf("Loaded new %s: %s\n", type.GetTypeName(), path.c_str());

		// And Return it
		return *contentEntry.C;
	}

	void DefaultContent::ClearContent() {
		for (std::vector<int>::size_type i = 0; i != m_ContentList.size(); i++)
			delete m_ContentList[i].C;
		m_ContentList.clear();

		printf("Cleared all Content\n");
	}
}