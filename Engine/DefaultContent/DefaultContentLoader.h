#pragma once

namespace Content { class IContent; }

namespace DefaultContent {
	// Use this function to create a new DefaultContent object without
	// including DefaultContent.h (and the includes that come with it)
	Content::IContent* LoadContent();
}