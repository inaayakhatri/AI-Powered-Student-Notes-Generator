/****************************************************************************
** Meta object code from reading C++ file 'CustomerPage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../CustomerPage.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CustomerPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN12CustomerPageE_t {};
} // unnamed namespace

template <> constexpr inline auto CustomerPage::qt_create_metaobjectdata<qt_meta_tag_ZN12CustomerPageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "CustomerPage",
        "addToCartRequested",
        "",
        "productName",
        "quantity",
        "removeFromCartRequested",
        "itemText",
        "cancelAllOrdersRequested",
        "completeAllOrdersRequested",
        "buyRequested",
        "trackOrdersRequested",
        "cancelOrderRequested",
        "changePasswordRequested",
        "logoutRequested",
        "themeToggled",
        "checked",
        "orderDetailsRequested",
        "QListWidgetItem*",
        "item"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'addToCartRequested'
        QtMocHelpers::SignalData<void(const QString &, int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 }, { QMetaType::Int, 4 },
        }}),
        // Signal 'removeFromCartRequested'
        QtMocHelpers::SignalData<void(const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Signal 'cancelAllOrdersRequested'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'completeAllOrdersRequested'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'buyRequested'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'trackOrdersRequested'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'cancelOrderRequested'
        QtMocHelpers::SignalData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'changePasswordRequested'
        QtMocHelpers::SignalData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'logoutRequested'
        QtMocHelpers::SignalData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'themeToggled'
        QtMocHelpers::SignalData<void(bool)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 15 },
        }}),
        // Signal 'orderDetailsRequested'
        QtMocHelpers::SignalData<void(QListWidgetItem *)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 17, 18 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CustomerPage, qt_meta_tag_ZN12CustomerPageE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject CustomerPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12CustomerPageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12CustomerPageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12CustomerPageE_t>.metaTypes,
    nullptr
} };

void CustomerPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CustomerPage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->addToCartRequested((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->removeFromCartRequested((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->cancelAllOrdersRequested(); break;
        case 3: _t->completeAllOrdersRequested(); break;
        case 4: _t->buyRequested(); break;
        case 5: _t->trackOrdersRequested(); break;
        case 6: _t->cancelOrderRequested(); break;
        case 7: _t->changePasswordRequested(); break;
        case 8: _t->logoutRequested(); break;
        case 9: _t->themeToggled((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 10: _t->orderDetailsRequested((*reinterpret_cast<std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (CustomerPage::*)(const QString & , int )>(_a, &CustomerPage::addToCartRequested, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (CustomerPage::*)(const QString & )>(_a, &CustomerPage::removeFromCartRequested, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (CustomerPage::*)()>(_a, &CustomerPage::cancelAllOrdersRequested, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (CustomerPage::*)()>(_a, &CustomerPage::completeAllOrdersRequested, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (CustomerPage::*)()>(_a, &CustomerPage::buyRequested, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (CustomerPage::*)()>(_a, &CustomerPage::trackOrdersRequested, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (CustomerPage::*)()>(_a, &CustomerPage::cancelOrderRequested, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (CustomerPage::*)()>(_a, &CustomerPage::changePasswordRequested, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (CustomerPage::*)()>(_a, &CustomerPage::logoutRequested, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (CustomerPage::*)(bool )>(_a, &CustomerPage::themeToggled, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (CustomerPage::*)(QListWidgetItem * )>(_a, &CustomerPage::orderDetailsRequested, 10))
            return;
    }
}

const QMetaObject *CustomerPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomerPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12CustomerPageE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CustomerPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void CustomerPage::addToCartRequested(const QString & _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void CustomerPage::removeFromCartRequested(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void CustomerPage::cancelAllOrdersRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CustomerPage::completeAllOrdersRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void CustomerPage::buyRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void CustomerPage::trackOrdersRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void CustomerPage::cancelOrderRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void CustomerPage::changePasswordRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void CustomerPage::logoutRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void CustomerPage::themeToggled(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1);
}

// SIGNAL 10
void CustomerPage::orderDetailsRequested(QListWidgetItem * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1);
}
QT_WARNING_POP
