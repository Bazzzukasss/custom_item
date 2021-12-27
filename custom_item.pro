QT += widgets
TEMPLATE = lib
CONFIG += staticlib  c++17
DESTDIR = ../bin

SOURCES += \
    src/CustomItem.cpp \
    src/CustomItemData.cpp \
    src/CustomItemDelegate.cpp \
    src/CustomItemFrame.cpp \
    src/CustomItemFrameHeader.cpp \
    src/CustomItemFrameView.cpp \
    src/CustomItemFrameWidget.cpp \
    src/CustomItemModel.cpp \
    src/CustomItemPropertiesView.cpp \
    src/CustomItemPropertyWidget.cpp \
    src/CustomItemSortFilterProxyModel.cpp \
    src/CustomItemTableModel.cpp \
    src/CustomItemTableMonitor.cpp \
    src/CustomItemTableView.cpp \
    src/CustomItemTreeModel.cpp \
    src/CustomItemTreeMonitor.cpp \
    src/CustomItemTreeView.cpp \
    src/CustomItemTypes.cpp \
    src/CustomItemWidget.cpp \
    src/CustomItemWidgets.cpp \
    src/qcustomplot.cpp

HEADERS += \
    inc/CustomItem.h \
    inc/CustomItemClasses.h \
    inc/CustomItemData.h \
    inc/CustomItemDelegate.h \
    inc/CustomItemFrame.h \
    inc/CustomItemFrameHeader.h \
    inc/CustomItemFrameView.h \
    inc/CustomItemFrameWidget.h \
    inc/CustomItemModel.h \
    inc/CustomItemPropertiesView.h \
    inc/CustomItemPropertyWidget.h \
    inc/CustomItemSortFilterProxyModel.h \
    inc/CustomItemTableModel.h \
    inc/CustomItemTableMonitor.h \
    inc/CustomItemTableView.h \
    inc/CustomItemTreeModel.h \
    inc/CustomItemTreeMonitor.h \
    inc/CustomItemTreeView.h \
    inc/CustomItemTypes.h \
    inc/CustomItemWidget.h \
    inc/CustomItemWidgets.h \
    inc/qcustomplot.h

INCLUDEPATH += inc

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
