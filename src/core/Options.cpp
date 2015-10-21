#include "Options.h"

#include <QtCore/QSettings>

void Options::save() const
{
  QSettings Settings;
  Settings.setValue("style",      _style);
  Settings.setValue("filename",   _filename);
  Settings.setValue("sort_type",  _sortType);
  Settings.setValue("media_type", _mediaType);
}

void Options::load()
{
  QSettings Settings;
  _style      =                       Settings.value("style",       _style).toString();
  _filename   =                       Settings.value("filename",    _filename).toString();
  _sortType   = (Collection::SortType)Settings.value("sort_type",   _sortType).toInt();
  _mediaType  =     (Media::MediaType)Settings.value("media_type",  _mediaType).toInt();
}
