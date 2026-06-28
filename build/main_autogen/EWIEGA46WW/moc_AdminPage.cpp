/****************************************************************************
** Meta object code from reading C++ file 'AdminPage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../AdminPage.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AdminPage.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN9AdminPageE_t {};
} // unnamed namespace

template <> constexpr inline auto AdminPage::qt_create_metaobjectdata<qt_meta_tag_ZN9AdminPageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "AdminPage",
        "addProductRequested",
        "",
        "name",
        "desc",
        "price",
        "qty",
        "removeProductRequested",
        "productName",
        "viewOrdersRequested",
        "clearOrdersRequested",
        "cancelAllOrdersRequested",
        "completeAllOrdersRequested",
        "confirmOrderRequested",
        "completeOrderRequested",
        "cancelOrderRequested",
        "deleteUserRequested",
        "changePasswordRequested",
        "viewSalesSummaryRequested",
        "logoutRequested",
        "themeToggled",
        "checked"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'addProductRequested'
        QtMocHelpers::SignalData<void(const QString &, const QString &, const QString &, const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 }, { QMetaType::QString, 4 }, { QMetaType::QString, 5 }, { QMetaType::QString, 6 },
        }}),
        // Signal 'removeProductRequested'
        QtMocHelpers::SignalData<void(const QString &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Signal 'viewOrdersRequested'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'clearOrdersRequested'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'cancelAllOrdersRequested'
        QtMocHelpers::SignalData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'completeAllOrdersRequested'
        QtMocHelpers::SignalData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'confirmOrderRequested'
        QtMocHelpers::SignalData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'completeOrderRequested'
        QtMocHelpers::SignalData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'cancelOrderRequested'
        QtMocHelpers::SignalData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'deleteUserRequested'
        QtMocHelpers::SignalData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'changePasswordRequested'
        QtMocHelpers::SignalData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'viewSalesSummaryRequested'
        QtMocHelpers::SignalData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'logoutRequested'
        QtMocHelpers::SignalData<void()>(19, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'themeToggled'
        QtMocHelpers::SignalData<void(bool)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 21 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<AdminPage, qt_meta_tag_ZN9AdminPageE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject AdminPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9AdminPageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9AdminPageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN9AdminPageE_t>.metaTypes,
    nullptr
} };

void AdminPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AdminPage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->addProductRequested((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4]))); break;
        case 1: _t->removeProductRequested((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->viewOrdersRequested(); break;
        case 3: _t->clearOrdersRequested(); break;
        case 4: _t->cancelAllOrdersRequested(); break;
        case 5: _t->completeAllOrdersRequested(); break;
        case 6: _t->confirmOrderRequested(); break;
        case 7: _t->completeOrderRequested(); break;
        case 8: _t->cancelOrderRequested(); break;
        case 9: _t->deleteUserRequested(); break;
        case 10: _t->changePasswordRequested(); break;
        case 11: _t->viewSalesSummaryRequested(); break;
        case 12: _t->logoutRequested(); break;
        case 13: _t->themeToggled((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (AdminPage::*)(const QString & , const QString & , const QString & , const QString & )>(_a, &AdminPage::addProductRequested, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (AdminPage::*)(const QString & )>(_a, &AdminPage::removeProductRequested, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (AdminPage::*)()>(_a, &AdminPage::viewOrdersRequested, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (AdminPage::*)()>(_a, &AdminPage::clearOrdersRequested, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (AdminPage::*)()>(_a, &AdminPage::cancelAllOrdersRequested, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (AdminPage::*)()>(_a, &AdminPage::completeAllOrdersRequested, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (AdminPage::*)()>(_a, &AdminPage::confirmOrderRequested, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (AdminPage::*)()>(_a, &AdminPage::completeOrderRequested, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (AdminPage::*)()>(_a, &AdminPage::cancelOrderRequested, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (AdminPage::*)()>(_a, &AdminPage::deleteUserRequested, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (AdminPage::*)()>(_a, &AdminPage::changePasswordRequested, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (AdminPage::*)()>(_a, &AdminPage::viewSalesSummaryRequested, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (AdminPage::*)()>(_a, &AdminPage::logoutRequested, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (AdminPage::*)(bool )>(_a, &AdminPage::themeToggled, 13))
            return;
    }
}

const QMetaObject *AdminPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AdminPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9AdminPageE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AdminPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void AdminPage::addProductRequested(const QString & _t1, const QString & _t2, const QString & _t3, const QString & _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2, _t3, _t4);
}

// SIGNAL 1
void AdminPage::removeProductRequested(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void AdminPage::viewOrdersRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void AdminPage::clearOrdersRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void AdminPage::cancelAllOrdersRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void AdminPage::completeAllOrdersRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void AdminPage::confirmOrderRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void AdminPage::completeOrderRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void AdminPage::cancelOrderRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void AdminPage::deleteUserRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void AdminPage::changePasswordRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void AdminPage::viewSalesSummaryRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void AdminPage::logoutRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void AdminPage::themeToggled(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 13, nullptr, _t1);
}
QT_WARNING_POP
