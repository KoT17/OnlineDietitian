import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { PickdietComponent } from './pickdiet.component';

describe('PickdietComponent', () => {
  let component: PickdietComponent;
  let fixture: ComponentFixture<PickdietComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ PickdietComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(PickdietComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
